#include <stdexcept>
#include "FalseRule.h"
#include "../../Formulas/BinaryLogicFormula.h"

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


    auto premise = premises[0].get();

    std::shared_ptr<Node> node = std::make_shared<Node>(premise->clone());

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

    contradictionIter->get()->setNext(node);
    node->addPrevious(*contradictionIter);
    deduction.conclusions.erase(deduction.findConclusion(contradiction));
    deduction.conclusions.push_back(node);
}
