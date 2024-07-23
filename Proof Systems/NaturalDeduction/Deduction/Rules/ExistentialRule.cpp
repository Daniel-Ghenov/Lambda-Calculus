#include <stdexcept>
#include <iostream>
#include "ExistentialRule.h"
#include "../../Formulas/TertiaryLogicFormula.h"
#include "../../Formulas/Variable.h"
#include "../../Formulas/BinaryLogicFormula.h"
#include "../../Formulas/FormulaFactory.h"


ExistentialRule::ExistentialRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::EXISTS, result, std::move(premises),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{

}

ExistentialRule::ExistentialRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises,
                                 std::vector<char> &&markers) : Rule(LogicOperation::EXISTS, result,
                                                                     std::move(premises), std::move(markers),
                                                                     getArgumentCount(result, argumentCountIntroduction,
                                                                                      argumentCountElimination))
{

}

void ExistentialRule::applyIntroduction(Deduction &deduction) const
{
    auto substitution = premises[0].get();

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

    auto variableIter = deduction.findConclusion(variable);

    if (variableIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid variable, must be in conclusions");
    }

    Formula *f = new BinaryLogicFormula(variable->clone(), proposition->clone(), LogicOperation::EXISTS);
    std::shared_ptr<Node> node = std::make_shared<Node>(f);

    substitutionIter->get()->setNext(node);
    variableIter->get()->setNext(node);

    node->addPrevious(*substitutionIter);
    node->addPrevious(*variableIter);

    deduction.conclusions.erase(deduction.findConclusion(substitution));
    deduction.conclusions.erase(deduction.findConclusion(variable));
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
    newNode->addPrevious(node);

    if (!markers.empty())
    {
        deduction.crossAssumptionsWithMarker(proposition, markers[0]);
    }
    else
    {
        propositionIter->get()->cross();
    }

    deduction.conclusions.erase(deduction.findConclusion(existential));
    deduction.conclusions.erase(deduction.findConclusion(node));
    deduction.conclusions.push_back(newNode);
}

std::unique_ptr<ExistentialRule> ExistentialRule::createRule(RuleResult result)
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

std::unique_ptr<ExistentialRule> ExistentialRule::createIntroductionRule()
{
    std::cout << "Enter the substitution formula:" << std::endl;
    std::string substitutionString;
    std::cin >> substitutionString;
    auto substitution = std::shared_ptr<Formula>(FormulaFactory::createFormula(substitutionString));

    return std::make_unique<ExistentialRule>(RuleResult::INTRODUCTION, std::vector{substitution});
}

std::unique_ptr<ExistentialRule> ExistentialRule::createEliminationRule()
{
    std::cout << "Enter the existential formula:" << std::endl;
    std::string existentialString;
    std::cin >> existentialString;
    auto existential = std::shared_ptr<Formula>(FormulaFactory::createFormula(existentialString));

    std::cout << "Enter the conclusion formula:" << std::endl;
    std::string conclusionString;
    std::cin >> conclusionString;
    auto conclusion = std::shared_ptr<Formula>(FormulaFactory::createFormula(conclusionString));

    std::vector<char> markers;
    std::cout << "Enter the marker for the assumption(leave empty if not needed):" << std::endl;
    char marker;
    if (std::cin.peek() == '\n' || std::cin.peek() == '\r')
    {
        std::cin.ignore();
        markers.push_back('\0');
    }
    else
    {
        std::cin >> marker;
        markers.push_back(marker);
    }
    return std::make_unique<ExistentialRule>(RuleResult::ELIMINATION, std::vector{existential, conclusion}, std::move(markers));
}

