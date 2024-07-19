#include <stdexcept>
#include "NegationRule.h"
#include "../../Formulas/BinaryLogicFormula.h"

NegationRule::NegationRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises) : Rule(
        LogicOperation::NOT, result, std::move(premises),
        getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{

}


NegationRule::NegationRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises,
                           std::vector<char> &&markers): Rule(LogicOperation::NOT, result, std::move(premises),
                                                              std::move(markers),
                                                              getArgumentCount(result, argumentCountIntroduction, argumentCountElimination))
{

}

void NegationRule::applyIntroduction(Deduction &deduction) const
{
    auto negation = premises[0].get();

    auto negationIter = deduction.findAssumption(negation);
    Node *node = negationIter->get();
    Deduction::getNodePointingToConclusion(UnaryLogicFormula::getFalse(), node);

    std::shared_ptr<Node> conclusion;
    if (negation->getType() == FormulaType::UNARY_LOGIC)
    {
        auto unary = dynamic_cast<UnaryLogicFormula *>(negation);
        conclusion = std::make_shared<Node>(unary->getOperand());
    } else
    {
        conclusion = std::make_shared<Node>(new UnaryLogicFormula(negation->clone()));
    }

    if (!markers.empty())
    {
        auto marker = markers[0];
        deduction.crossAssumptionsWithMarker(negation, marker);
    } else
    {
        negationIter->get()->cross();
    }

    node->setNext(conclusion);
    conclusion->addPrevious(*negationIter);
    deduction.conclusions.erase(deduction.findConclusion(negation));
    deduction.conclusions.push_back(conclusion);
}

void NegationRule::applyElimination(Deduction &deduction) const
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
