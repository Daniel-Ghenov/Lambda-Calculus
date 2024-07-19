#include <stdexcept>
#include "ImplicationRule.h"
#include "../../Formulas/BinaryLogicFormula.h"

ImplicationRule::ImplicationRule(std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::IMPLIES, RuleResult::ELIMINATION, std::move(premises),
        argumentCountElimination)
{

}

ImplicationRule::ImplicationRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises,
                                 std::vector<char> &&markers) : Rule(
        LogicOperation::IMPLIES, result, std::move(premises), std::move(markers),
        getArgumentCount(RuleResult::INTRODUCTION, argumentCountIntroduction, argumentCountElimination))
{

}

void ImplicationRule::applyIntroduction(Deduction &deduction) const
{

    const auto ruleAssumed = premises[0].get();
    const auto conclusion = premises[1].get();

    const char marker = markers[0];

    auto i = deduction.findAssumption(ruleAssumed);

    if (i == deduction.assumptions.end())
    {
        throw std::invalid_argument("Invalid assumption");
    }
    Node *node = (*i).get();
    Deduction::getNodePointingToConclusion(conclusion, node);

    Formula *f = new BinaryLogicFormula(ruleAssumed->clone(), conclusion->clone(), LogicOperation::IMPLIES);
    std::shared_ptr<Node> newNode = std::make_shared<Node>(f);
    node->setNext(newNode);

    auto assumed = deduction.findConclusion(node);

    newNode->addPrevious(*assumed);
    deduction.crossAssumptionsWithMarker(f, marker);

    deduction.conclusions.erase(deduction.findConclusion(ruleAssumed));
    deduction.conclusions.push_back(node->getNextShared());
}

void ImplicationRule::applyElimination(Deduction &deduction) const
{

    const auto implication = premises[0].get();

    if (implication->getType() != FormulaType::BINARY_LOGIC)
    {
        throw std::invalid_argument("Invalid implication");
    }

    const auto binary = dynamic_cast<BinaryLogicFormula *>(implication);

    if (binary->getOperation() != LogicOperation::IMPLIES)
    {
        throw std::invalid_argument("Invalid implication");
    }

    const Formula *implied = binary->getLeftOperand();

    auto implIter = deduction.findConclusion(implication);

    if (implIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid implication, must be in conclusions");
    }

    auto impliedIter = deduction.findConclusion(implied);

    if (impliedIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid implied, must be in conclusions");
    }

    std::shared_ptr<Node> node = std::make_shared<Node>(binary->getRightOperand()->clone());

    implIter->get()->setNext(node);
    deduction.conclusions.erase(deduction.findConclusion(implication));
    deduction.conclusions.push_back(node);
    impliedIter->get()->setNext(node);
    deduction.conclusions.erase(deduction.findConclusion(implied));

    node->addPrevious(*implIter);
    node->addPrevious(*impliedIter);
}
