#include <stdexcept>
#include <iostream>
#include "ConjunctionRule.h"
#include "../../Formulas/BinaryLogicFormula.h"
#include "../../Formulas/FormulaFactory.h"

ConjunctionRule::ConjunctionRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::AND, result, std::move(premises),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{
}

void ConjunctionRule::applyIntroduction(Deduction &deduction) const
{
    const auto conjunction = premises[0].get();

    if (conjunction->getType() != FormulaType::BINARY_LOGIC)
    {
        throw std::invalid_argument("Invalid conjunction");
    }

    const auto binary = dynamic_cast<BinaryLogicFormula *>(conjunction);

    if (binary == nullptr || binary->getOperation() != LogicOperation::AND)
    {
        throw std::invalid_argument("Invalid conjunction");
    }

    const auto left = binary->getLeftOperand();
    const auto right = binary->getRightOperand();

    auto leftIter = deduction.findConclusion(left);

    if (leftIter == deduction.assumptions.end())
    {
        throw std::invalid_argument("Invalid left operand");
    }

    auto rightIter = deduction.findConclusion(right);

    if (rightIter == deduction.assumptions.end())
    {
        throw std::invalid_argument("Invalid right operand");
    }

    std::shared_ptr<Node> node = std::make_shared<Node>(binary->clone());

    leftIter->get()->setNext(node);
    rightIter->get()->setNext(node);

    node->addPrevious(*leftIter);
    node->addPrevious(*rightIter);

    deduction.conclusions.erase(deduction.findConclusion(left));
    deduction.conclusions.erase(deduction.findConclusion(right));
    deduction.conclusions.push_back(node);
}

void ConjunctionRule::applyElimination(Deduction &deduction) const
{
    const auto expected = premises[0].get();
    const auto conclusion = premises[1].get();
    if (expected->getType() != FormulaType::BINARY_LOGIC)
    {
        throw std::invalid_argument("Invalid conjunction");
    }

    const auto conjunction = dynamic_cast<BinaryLogicFormula *>(expected);

    if ((conjunction)->getOperation() != LogicOperation::AND)
    {
        throw std::invalid_argument("Invalid conjunction");
    }

    auto i = deduction.findConclusion(expected);

    if (i == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid conjunction, must be in conclusions");
    }

    const auto left = conjunction->getLeftOperand();
    const auto right = conjunction->getRightOperand();

    if (!(*left == *conclusion) && !(*right == *conclusion))
    {
        throw std::invalid_argument("Invalid conclusion to eliminate");
    }


    std::shared_ptr<Node> node;
    if (*left == *conclusion)
    {
        node = std::make_shared<Node>(left->clone());
    } else
    {
        node = std::make_shared<Node>(right->clone());
    }

    i->get()->setNext(node);
    deduction.conclusions.erase(i);
    deduction.conclusions.push_back(node);
}

std::unique_ptr<ConjunctionRule> ConjunctionRule::createRule(RuleResult result)
{
    switch (result)
    {
        case RuleResult::INTRODUCTION:
            return createIntroductionRule();
        case RuleResult::ELIMINATION:
            return createEliminationRule();
        default:
            throw std::invalid_argument("Invalid rule result");
    }
}

std::unique_ptr<ConjunctionRule> ConjunctionRule::createIntroductionRule()
{
    std::cout << "Enter the conjunction formula:" << std::endl;
    std::string conjunctionString;
    std::cin >> conjunctionString;
    auto conjunction = std::shared_ptr<Formula>(FormulaFactory::createFormula(conjunctionString));
    return std::make_unique<ConjunctionRule>(RuleResult::INTRODUCTION, std::vector{conjunction});
}

std::unique_ptr<ConjunctionRule> ConjunctionRule::createEliminationRule()
{
    std::cout << "Enter the conjunction formula:" << std::endl;
    std::string conjunctionString;
    std::cin >> conjunctionString;
    auto conjunction = std::shared_ptr<Formula>(FormulaFactory::createFormula(conjunctionString));

    std::cout << "Enter the result:" << std::endl;
    std::string resultString;
    std::cin >> resultString;
    auto result = std::shared_ptr<Formula>(FormulaFactory::createFormula(resultString));
    return std::make_unique<ConjunctionRule>(RuleResult::INTRODUCTION, std::vector{conjunction, result});
}

