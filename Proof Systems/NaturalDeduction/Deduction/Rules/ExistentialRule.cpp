#include <stdexcept>
#include "ExistentialRule.h"
#include "../../Formulas/TertiaryLogicFormula.h"
#include "../../Formulas/Variable.h"
#include "../../Formulas/BinaryLogicFormula.h"


ExistentialRule::ExistentialRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::EXISTS, result, std::move(premises),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{
}

void ExistentialRule::applyIntroduction(Deduction &deduction) const
{
    auto substitution = premises[0].get();
    auto var = premises[1].get();

    if (substitution->getType() != FormulaType::TERTIARY_LOGIC)
    {
        throw std::invalid_argument("Invalid substitution");
    }

    auto tertiary = dynamic_cast<TertiaryLogicFormula *>(substitution);

    if (tertiary->getOperation() != LogicOperation::SUBSTITUTION)
    {
        throw std::invalid_argument("Invalid substitution");
    }

    auto proposition = tertiary->getMain();
    auto variable = tertiary->getLeft();

    auto substitutionIter = deduction.findConclusion(substitution);

    if (substitutionIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid substitution, must be in conclusions");
    }

    auto variableIter = deduction.findConclusion(var);

    if (variableIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid variable, must be in conclusions");
    }

    Formula *f = new BinaryLogicFormula(var->clone(), proposition->clone(), LogicOperation::EXISTS);
    std::shared_ptr<Node> node = std::make_shared<Node>(f);

    substitutionIter->get()->setNext(node);
    variableIter->get()->setNext(node);

    node->addPrevious(*substitutionIter);
    node->addPrevious(*variableIter);

    deduction.conclusions.erase(deduction.findConclusion(substitution));
    deduction.conclusions.erase(deduction.findConclusion(var));
    deduction.conclusions.push_back(node);
}

void ExistentialRule::applyElimination(Deduction &deduction) const
{

    auto existential = premises[0].get();
    auto conclusion = premises[1].get();

    if (existential->getType() != FormulaType::BINARY_LOGIC)
    {
        throw std::invalid_argument("Invalid existential");
    }

    auto binary = dynamic_cast<BinaryLogicFormula *>(existential);

    if (binary->getOperation() != LogicOperation::EXISTS)
    {
        throw std::invalid_argument("Invalid existential");
    }

    auto variable = binary->getLeftOperand();

    if (variable->getType() != FormulaType::VARIABLE)
    {
        throw std::invalid_argument("Invalid variable");
    }

    auto var = dynamic_cast<Variable *>(variable);

    auto proposition = binary->getRightOperand();

    auto propositionIter = deduction.findAssumption(proposition);

    if (propositionIter == deduction.assumptions.end())
    {
        throw std::invalid_argument("Invalid proposition");
    }
    Node *node = propositionIter->get();
    Deduction::getNodePointingToConclusion(conclusion, node);
    std::set<char> formulaSet = proposition->getFreeVariables();
    if (formulaSet.find(var->getVariable()) != formulaSet.end())
    {
        throw std::invalid_argument("Invalid variable");
    }
    std::set<char> pathVariables = node->getFreeVariables();
    for (const char &c: proposition->getFreeVariables())
    {
        pathVariables.erase(c);
    }
    if (pathVariables.find(var->getVariable()) != pathVariables.end())
    {
        throw std::invalid_argument("Invalid variable");
    }

    std::shared_ptr<Node> newNode = std::make_shared<Node>(conclusion->clone());

    node->setNext(newNode);

    newNode->addPrevious(*propositionIter);

    deduction.conclusions.erase(deduction.findConclusion(existential));
    deduction.conclusions.erase(deduction.findConclusion(node));
    deduction.conclusions.push_back(newNode);
}

