#include <stdexcept>
#include <iostream>
#include "FalseRule.h"
#include "../../Formulas/BinaryLogicFormula.h"
#include "../../Formulas/FormulaFactory.h"

FalseRule::FalseRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(LogicOperation::FALSE,
                                                                                                 result,
                                                                                                 std::move(premises),
                                                                                                 getArgumentCount(
                                                                                                         result,
                                                                                                         argumentCountIntroduction,
                                                                                                         argumentCountElimination))
{

}

void FalseRule::applyElimination(Deduction &deduction) const
{
    auto falseIter = deduction.findConclusion(UnaryLogicFormula::getFalse());

    if (falseIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid false, must be in conclusions");
    }


    auto conclusion = premises[0].get();

    std::shared_ptr<Node> node = std::make_shared<Node>(conclusion->clone());

    falseIter->get()->setNext(node);
    node->addPrevious(*falseIter);
    deduction.conclusions.erase(falseIter);
    deduction.conclusions.push_back(node);
}

void FalseRule::applyIntroduction(Deduction &deduction) const
{
    auto premise = premises[0].get();
    Formula *notNegated;
    Formula *negated;

    if (premise->getType() == FormulaType::UNARY_LOGIC)
    {
        auto unary = dynamic_cast<UnaryLogicFormula *>(premise);
        if (unary->getOperation() != LogicOperation::NOT)
        {
            throw std::invalid_argument("Invalid negation");
        }
        notNegated = unary->getOperand();
        negated = unary;
    } else
    {
        notNegated = premise;
        negated = new UnaryLogicFormula(premise->clone());
    }

    Formula *contradiction = new BinaryLogicFormula(notNegated->clone(), negated->clone(), LogicOperation::AND);

    auto contradictionIter = deduction.findConclusion(contradiction);

    std::shared_ptr<Node> node = std::make_shared<Node>(UnaryLogicFormula::getFalse());

    if (contradictionIter == deduction.conclusions.end())
    {
        throw std::invalid_argument("Invalid contradiction, must be in conclusions");
    }

    contradictionIter->get()->setNext(node);
    node->addPrevious(*contradictionIter);
    deduction.conclusions.erase(deduction.findConclusion(contradiction));
    deduction.conclusions.push_back(node);
}

std::unique_ptr<FalseRule> FalseRule::createRule(RuleResult result)
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

std::unique_ptr<FalseRule> FalseRule::createIntroductionRule()
{
    std::cout<< "Enter the conclusion that has a contradiction: "<< std::endl;
    std::string formulaString;
    std::cin >> formulaString;
    auto formula = std::shared_ptr<Formula>(FormulaFactory::createFormula(formulaString));

    return std::make_unique<FalseRule>(RuleResult::INTRODUCTION, std::vector{formula});
}

std::unique_ptr<FalseRule> FalseRule::createEliminationRule()
{
    std::cout<< "Enter the formula that is concluded from false conclusion: "<< std::endl;
    std::string formulaString;
    std::cin >> formulaString;
    auto formula = std::shared_ptr<Formula>(FormulaFactory::createFormula(formulaString));

    return std::make_unique<FalseRule>(RuleResult::ELIMINATION, std::vector{formula});
}
