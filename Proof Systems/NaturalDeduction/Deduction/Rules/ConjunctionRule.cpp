#include <stdexcept>
#include "ConjunctionRule.h"
#include "../../Formulas/BinaryLogicFormula.h"

ConjunctionRule::ConjunctionRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::AND, result, std::move(premises))
{

}

int ConjunctionRule::getRuleArgumentCountIntroduction() const
{
    return 1;
}

int ConjunctionRule::getRuleArgumentCountElimination() const
{
    return 2;
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

    if (!(*left == *conclusion) &&
        !(*right == *conclusion))
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
