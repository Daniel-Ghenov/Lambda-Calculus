#include <memory>
#include <stdexcept>
#include "RuleFactory.h"
#include "UniversalRule.h"
#include "ExistentialRule.h"
#include "ConjunctionRule.h"
#include "DisjunctionRule.h"
#include "ImplicationRule.h"
#include "NegationRule.h"
#include "FalseRule.h"

std::shared_ptr<Rule> RuleFactory::createRule(LogicOperation type,RuleResult result, std::vector<std::shared_ptr<Formula>>&& premises)
{
    switch (type)
    {
        case LogicOperation::AND:
            return std::make_shared<ConjunctionRule>(result, std::move(premises));
        case LogicOperation::OR:
            return std::make_shared<DisjunctionRule>(result, std::move(premises));
        case LogicOperation::NOT:
            return std::make_shared<NegationRule>(result, std::move(premises));
        case LogicOperation::FALSE:
            return std::make_shared<FalseRule>(result, std::move(premises));
        case LogicOperation::FOR_EACH:
            return std::make_shared<UniversalRule>(result, std::move(premises));
        case LogicOperation::EXISTS:
            return std::make_shared<ExistentialRule>(result, std::move(premises));
        case LogicOperation::SUBSTITUTION:
        case LogicOperation::BIDIRECTIONAL_IMPLIES:
        default:
            throw std::invalid_argument("logic operation not supported");
    }
}

std::shared_ptr<Rule> RuleFactory::createRule(LogicOperation type,RuleResult result, std::vector<std::shared_ptr<Formula>>&& premises, std::vector<char> &&markers)
{
    switch (type)
    {
        case LogicOperation::IMPLIES:
            return std::make_shared<ImplicationRule>(result, std::move(premises), std::move(markers));
        case LogicOperation::SUBSTITUTION:
        case LogicOperation::BIDIRECTIONAL_IMPLIES:
        default:
            throw std::invalid_argument("logic operation not supported");
    }

}