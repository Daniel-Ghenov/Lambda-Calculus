#include <stdexcept>
#include "DisjunctionRule.h"
#include "../../Formulas/BinaryLogicFormula.h"
#include "../Node.h"

DisjunctionRule::DisjunctionRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::OR, result, std::move(premises))
{

}

int DisjunctionRule::getRuleArgumentCountIntroduction() const
{
    return 2;
}

int DisjunctionRule::getRuleArgumentCountElimination() const
{
    return 2;
}

void DisjunctionRule::applyElimination(Deduction &deduction) const
{
    auto disjunction = premises[0].get();
    auto implied = premises[1].get();

    if (disjunction->getType() != FormulaType::BINARY_LOGIC)
    {
        throw std::invalid_argument("Invalid disjunction");
    }

    auto binary = dynamic_cast<BinaryLogicFormula *>(disjunction);
    if (binary == nullptr || binary->getOperation() != LogicOperation::OR)
    {
        throw std::invalid_argument("Invalid disjunction");
    }

    auto disConclusion = deduction.findConclusion(disjunction);

    if (disConclusion == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid disjunction, must be in conclusions");
    }

    auto left = binary->getLeftOperand();
    auto right = binary->getRightOperand();

    auto leftIter = deduction.findAssumption(left);
    if (leftIter == deduction.assumptions.end())
    {
        throw std::invalid_argument("Invalid left operand");
    }

    auto rightIter = deduction.findAssumption(right);
    if (rightIter == deduction.assumptions.end())
    {
        throw std::invalid_argument("Invalid right operand");
    }
    auto node = (*leftIter).get();
    Deduction::getNodePointingToConclusion(implied, node);

    auto nodeRight = (*rightIter).get();
    Deduction::getNodePointingToConclusion(implied, nodeRight);

    std::shared_ptr<Node> newNode = std::make_shared<Node>(implied->clone());
    node->setNext(newNode);
    nodeRight->setNext(newNode);
    disConclusion->get()->setNext(newNode);

    newNode->addPrevious(*leftIter);
    newNode->addPrevious(*rightIter);
    newNode->addPrevious(disConclusion->get());

    leftIter->get()->cross();
    rightIter->get()->cross();
    deduction.conclusions.push_back(newNode);

    deduction.conclusions.erase(deduction.findConclusion(disjunction));
    deduction.conclusions.erase(deduction.findConclusion(node));
    deduction.conclusions.erase(deduction.findConclusion(nodeRight));
}

void DisjunctionRule::applyIntroduction(Deduction &deduction) const
{
    auto disjunction = premises[0].get();
    auto current = premises[1].get();

    if (disjunction->getType() != FormulaType::BINARY_LOGIC)
    {
        throw std::invalid_argument("Invalid disjunction");
    }

    auto binary = dynamic_cast<BinaryLogicFormula *>(disjunction);

    if (binary == nullptr || binary->getOperation() != LogicOperation::OR)
    {
        throw std::invalid_argument("Invalid disjunction");
    }

    auto left = binary->getLeftOperand();
    auto right = binary->getRightOperand();

    if (!(*left == *current) &&
        !(*right == *current))
    {
        throw std::invalid_argument("Invalid current");
    }

    auto leftIter = deduction.findConclusion(current);

    if (leftIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid current, must be in conclusions");
    }

    std::shared_ptr<Node> node = std::make_shared<Node>(disjunction->clone());
    leftIter->get()->setNext(node);
    node->addPrevious(*leftIter);

    deduction.conclusions.erase(deduction.findConclusion(current));
    deduction.conclusions.push_back(node);
}
