#include <memory>
#include <stdexcept>
#include <iostream>
#include "RuleFactory.h"
#include "UniversalRule.h"
#include "ExistentialRule.h"
#include "ConjunctionRule.h"
#include "DisjunctionRule.h"
#include "ImplicationRule.h"
#include "NegationRule.h"
#include "FalseRule.h"
#include "../../Formulas/FormulaFactory.h"

std::shared_ptr<Rule> RuleFactory::createRule(LogicOperation type,RuleResult result, std::vector<std::shared_ptr<Formula>>&& premises)
{
    switch (type)
    {
        case LogicOperation::AND:
            return std::make_shared<ConjunctionRule>(result, std::move(premises));
        case LogicOperation::IMPLIES:
            return std::make_shared<ImplicationRule>(result, std::move(premises));
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

std::shared_ptr<Rule> RuleFactory::createRule(LogicOperation type,RuleResult result, std::vector<std::shared_ptr<Formula>>&& premises, std::vector<char>&& markers)
{
    switch (type)
    {
        case LogicOperation::OR:
            return std::make_shared<DisjunctionRule>(result, std::move(premises), std::move(markers));
        case LogicOperation::EXISTS:
            return std::make_shared<ExistentialRule>(result, std::move(premises), std::move(markers));
        case LogicOperation::NOT:
            return std::make_shared<NegationRule>(result, std::move(premises), std::move(markers));
        case LogicOperation::IMPLIES:
            return std::make_shared<ImplicationRule>(result, std::move(premises), std::move(markers));
        case LogicOperation::SUBSTITUTION:
        case LogicOperation::BIDIRECTIONAL_IMPLIES:
        default:
            throw std::invalid_argument("logic operation not supported");
    }

}

std::shared_ptr<Rule> RuleFactory::createRule()
{

    LogicOperation operation = getLogicOperation();
    RuleResult ruleResult = getRuleResult();

    switch (operation)
    {
        case LogicOperation::AND:
            return ConjunctionRule::createRule(ruleResult);
        case LogicOperation::IMPLIES:
            return ImplicationRule::createRule(ruleResult);
        case LogicOperation::OR:
            return DisjunctionRule::createRule(ruleResult);
        case LogicOperation::NOT:
            return NegationRule::createRule(ruleResult);
        case LogicOperation::FALSE:
            return FalseRule::createRule(ruleResult);
        case LogicOperation::FOR_EACH:
            return UniversalRule::createRule(ruleResult);
        case LogicOperation::EXISTS:
            return ExistentialRule::createRule(ruleResult);
        case LogicOperation::SUBSTITUTION:
        case LogicOperation::BIDIRECTIONAL_IMPLIES:
        default:
            throw std::invalid_argument("logic operation not supported");
    }
}

LogicOperation RuleFactory::getLogicOperation()
{
    while (true){
        std::cout << "Enter rule type:" << std::endl;
        std::cout << "1. Conjunction" << std::endl;
        std::cout << "2. Disjunction" << std::endl;
        std::cout << "3. Implication" << std::endl;
        std::cout << "4. Negation" << std::endl;
        std::cout << "5. Universal" << std::endl;
        std::cout << "6. Existential" << std::endl;
        std::cout << "7. Substitution" << std::endl;
        std::cout << "8. False" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                return LogicOperation::AND;
            case 2:
                return LogicOperation::OR;
            case 3:
                return LogicOperation::IMPLIES;
            case 4:
                return LogicOperation::NOT;
            case 5:
                return LogicOperation::FOR_EACH;
            case 6:
                return LogicOperation::EXISTS;
            case 7:
                return LogicOperation::SUBSTITUTION;
            case 8:
                return LogicOperation::FALSE;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }
}

RuleResult RuleFactory::getRuleResult()
{
    while (true){
        std::cout << "Enter rule result:" << std::endl;
        std::cout << "1. Introduction" << std::endl;
        std::cout << "2. Elimination" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice)
        {
            case 1:
                return RuleResult::INTRODUCTION;
            case 2:
                return RuleResult::ELIMINATION;
            default:
                std::cout << "Invalid choice" << std::endl;
        }
    }
}
