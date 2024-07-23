#include <stdexcept>
#include <iostream>
#include "UniversalRule.h"
#include "../../Formulas/BinaryLogicFormula.h"
#include "../../Formulas/TertiaryLogicFormula.h"
#include "../../Formulas/Variable.h"
#include "../../Formulas/FormulaFactory.h"

UniversalRule::UniversalRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::FOR_EACH, result, std::move(premises),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{
}


void UniversalRule::applyIntroduction(Deduction &deduction) const
{
    auto proposition = premises[0].get();

    auto propositionIter = deduction.findConclusion(proposition);

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

std::unique_ptr<UniversalRule> UniversalRule::createRule(RuleResult result)
{
    switch (result)
    {
        case RuleResult::INTRODUCTION:
            return createIntroductionRule();
        case RuleResult::ELIMINATION:
            return createEliminationRule();
        default:
            throw std::invalid_argument("Invalid result");
    }
}

std::unique_ptr<UniversalRule> UniversalRule::createIntroductionRule()
{
    std::cout<<"Enter the proposition of the universal:"<<std::endl;
    std::string formulaString;
    std::cin>>formulaString;
    auto formula = std::shared_ptr<Formula>(FormulaFactory::createFormula(formulaString));

    return std::make_unique<UniversalRule>(RuleResult::INTRODUCTION, std::vector{formula});
}

std::unique_ptr<UniversalRule> UniversalRule::createEliminationRule()
{
    std::cout<<"Enter the universal formula:"<<std::endl;
    std::string universalString;
    std::cin>>universalString;
    auto universal = std::shared_ptr<Formula>(FormulaFactory::createFormula(universalString));

    std::cout<<"Enter the variable that is a conclusion"<<std::endl;
    std::string variableString;
    std::cin>>variableString;
    auto variable = std::shared_ptr<Formula>(FormulaFactory::createFormula(variableString));

    return std::make_unique<UniversalRule>(RuleResult::ELIMINATION, std::vector{universal, variable});
}


