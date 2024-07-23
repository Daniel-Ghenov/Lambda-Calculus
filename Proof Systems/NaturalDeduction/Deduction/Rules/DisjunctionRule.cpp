#include <stdexcept>
#include <iostream>
#include "DisjunctionRule.h"
#include "../../Formulas/BinaryLogicFormula.h"
#include "../Node.h"
#include "../../Formulas/FormulaFactory.h"

DisjunctionRule::DisjunctionRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::OR, result, std::move(premises),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{

}

DisjunctionRule::DisjunctionRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises,
                                 std::vector<char> &&markers): Rule(
        LogicOperation::OR, result, std::move(premises), std::move(markers),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{

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

    if (markers.empty()){
        leftIter->get()->cross();
        rightIter->get()->cross();
    }
    else if (markers.size() == 1)
    {
        auto marker = markers[0];
        deduction.crossAssumptionsWithMarker(left, marker);
    }
    else
    {
        auto leftMarker = markers[0];
        auto rightMarker = markers[1];
        deduction.crossAssumptionsWithMarker(left, leftMarker);
        deduction.crossAssumptionsWithMarker(right, rightMarker);
    }
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

    if (!(*left == *current) && !(*right == *current))
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

std::unique_ptr<DisjunctionRule> DisjunctionRule::createRule(RuleResult result)
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

std::unique_ptr<DisjunctionRule> DisjunctionRule::createIntroductionRule()
{
    std::cout<<"Enter the expected disjunction:"<<std::endl;
    std::string disjunctionString;
    std::cin>>disjunctionString;
    auto disjunction = std::shared_ptr<Formula>(FormulaFactory::createFormula(disjunctionString));

    std::cout<<"Enter the current formula:"<<std::endl;
    std::string currentString;
    std::cin>>currentString;
    auto current = std::shared_ptr<Formula>(FormulaFactory::createFormula(currentString));

    return std::make_unique<DisjunctionRule>(RuleResult::INTRODUCTION, std::vector{disjunction, current});
}

std::unique_ptr<DisjunctionRule> DisjunctionRule::createEliminationRule()
{
    std::cout<<"Enter the current disjunction:"<<std::endl;
    std::string disjunctionString;
    std::cin>>disjunctionString;
    auto disjunction = std::shared_ptr<Formula>(FormulaFactory::createFormula(disjunctionString));

    std::cout<<"Enter the implied formula:"<<std::endl;
    std::string impliedString;
    std::cin>>impliedString;
    auto implied = std::shared_ptr<Formula>(FormulaFactory::createFormula(impliedString));

    std::vector<char> markers;
    for (size_t i = 0; i < 2; i++)
    {
        std::cout<<"Enter the marker for the "<<(i == 0 ? "left" : "right")<<" operand (leave empty if no marker is needed):"<<std::endl;
        char marker;
        if (std::cin.peek() == '\n' || std::cin.peek() == '\r')
        {
            std::cin.ignore();
            markers.push_back('\0');
            continue;
        }
        std::cin>>marker;
        markers.push_back(marker);
    }
    return std::make_unique<DisjunctionRule>(RuleResult::ELIMINATION, std::vector{disjunction, implied}, std::move(markers));
}
