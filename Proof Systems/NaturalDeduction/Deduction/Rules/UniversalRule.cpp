#include <stdexcept>
#include "UniversalRule.h"
#include "../../Formulas/BinaryLogicFormula.h"
#include "../../Formulas/TertiaryLogicFormula.h"
#include "../../Formulas/Variable.h"

UniversalRule::UniversalRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::FOR_EACH, result, std::move(premises),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{
}


void UniversalRule::applyIntroduction(Deduction &deduction) const
{
    auto proposition = premises[0].get();

    auto propositionIter = deduction.findAssumption(proposition);

    if (propositionIter == deduction.assumptions.end())
    {
        throw std::invalid_argument("Invalid proposition");
    }

    std::set<char> free = proposition->getFreeVariables();

    char x = Deduction::getXNotInFormula(proposition);
    Formula *variable = new Variable(x);
    Formula *universal = new BinaryLogicFormula(variable, proposition->clone(), LogicOperation::FOR_EACH);

    std::shared_ptr<Node> node = std::make_shared<Node>(universal);

    propositionIter->get()->setNext(node);
    node->addPrevious(*propositionIter);

    deduction.conclusions.erase(deduction.findConclusion(proposition));
    deduction.conclusions.push_back(node);

}

void UniversalRule::applyElimination(Deduction &deduction) const
{

    auto universal = premises[0].get();
    auto variable = premises[1].get();

    if (universal->getType() != FormulaType::BINARY_LOGIC)
    {
        throw std::invalid_argument("Invalid universal");
    }

    auto binary = dynamic_cast<BinaryLogicFormula *>(universal);

    if (binary->getOperation() != LogicOperation::FOR_EACH)
    {
        throw std::invalid_argument("Invalid universal");
    }

    auto proposition = binary->getRightOperand();
    auto forAllVariable = binary->getLeftOperand();

    auto universalIter = deduction.findConclusion(universal);

    if (universalIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid universal, must be in conclusions");
    }

    auto variableIter = deduction.findConclusion(variable);

    if (variableIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid variable, must be in conclusions");
    }

    Formula *f = new TertiaryLogicFormula(proposition->clone(), forAllVariable->clone(), variable->clone());
    std::shared_ptr<Node> node = std::make_shared<Node>(f);

    universalIter->get()->setNext(node);
    variableIter->get()->setNext(node);

    node->addPrevious(*universalIter);
    node->addPrevious(*variableIter);

    deduction.conclusions.erase(deduction.findConclusion(universal));
    deduction.conclusions.erase(deduction.findConclusion(variable));
    deduction.conclusions.push_back(node);
}


