#include <stdexcept>
#include <iostream>
#include "ImplicationRule.h"
#include "../../Formulas/BinaryLogicFormula.h"
#include "../../Formulas/FormulaFactory.h"

ImplicationRule::ImplicationRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::IMPLIES, result, std::move(premises),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{

}

ImplicationRule::ImplicationRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises,
                                 std::vector<char> &&markers) : Rule(
        LogicOperation::IMPLIES, result, std::move(premises), std::move(markers),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{

}

void ImplicationRule::applyIntroduction(Deduction &deduction) const
{

    const auto ruleAssumed = premises[0].get();
    const auto conclusion = premises[1].get();


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
    if (!markers.empty())
    {
        const char marker = markers[0];
        deduction.crossAssumptionsWithMarker(ruleAssumed, marker);
    } else {
        (*i)->cross();
    }

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

std::unique_ptr<ImplicationRule> ImplicationRule::createRule(RuleResult result)
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

std::unique_ptr<ImplicationRule> ImplicationRule::createIntroductionRule()
{
    std::cout<<"Enter the premise of the implication:"<<std::endl;
    std::string formulaString;
    std::cin>>formulaString;
    auto formula = std::shared_ptr<Formula>(FormulaFactory::createFormula(formulaString));

    std::cout<<"Enter the conclusion of the implication:"<<std::endl;
    std::string conclusionString;
    std::cin>>conclusionString;
    auto conclusion = std::shared_ptr<Formula>(FormulaFactory::createFormula(conclusionString));

    std::cout<<"Enter the marker (leave empty if not needed):"<<std::endl;
    char marker;
    if (std::cin.peek() == '\n' || std::cin.peek() == '\r')
    {
        return std::make_unique<ImplicationRule>(RuleResult::INTRODUCTION, std::vector{formula, conclusion});
    }

    std::cin>>marker;
    return std::make_unique<ImplicationRule>(RuleResult::INTRODUCTION, std::vector{formula, conclusion}, std::vector{marker});
}

std::unique_ptr<ImplicationRule> ImplicationRule::createEliminationRule()
{
    std::cout<<"Enter the implication:"<<std::endl;
    std::string implicationString;
    std::cin>>implicationString;
    auto implication = std::shared_ptr<Formula>(FormulaFactory::createFormula(implicationString));

    return std::make_unique<ImplicationRule>(RuleResult::ELIMINATION, std::vector{implication});

}
