#include <stdexcept>
#include <iostream>
#include <algorithm>
#include "Deduction.h"
#include "../Formulas/BinaryLogicFormula.h"
#include "../Formulas/Variable.h"
#include "../Formulas/TertiaryLogicFormula.h"

void Deduction::applyRule(Rule rule)
{
    switch (rule.getType())
    {

        case LogicOperation::AND:
            switch (rule.getResult())
            {
                case RuleResult::INTRODUCTION:
                    applyConjunctionIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyConjunctionElimination(rule);
                    break;
            }
            break;
        case LogicOperation::OR:
            switch (rule.getResult())
            {
                case RuleResult::INTRODUCTION:
                    applyDisjunctionIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyDisjunctionElimination(rule);
                    break;
            }
            break;
        case LogicOperation::IMPLIES:
            switch (rule.getResult())
            {
                case RuleResult::INTRODUCTION:
                    applyImplicationIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyImplicationElimination(rule);
                    break;
            }
            break;
        case LogicOperation::NOT:
            switch (rule.getResult())
            {
                case RuleResult::INTRODUCTION:
                    applyNegationIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyNegationElimination(rule);
                    break;
            }
            break;
        case LogicOperation::FOR_EACH:
            switch (rule.getResult())
            {
                case RuleResult::INTRODUCTION:
                    applyUniversalIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyUniversalElimination(rule);
                    break;
            }
            break;
        case LogicOperation::EXISTS:
            switch (rule.getResult())
            {
                case RuleResult::INTRODUCTION:
                    applyExistentialIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyExistentialElimination(rule);
                    break;
            }
            break;
        case LogicOperation::FALSE:
            switch (rule.getResult())
            {
                case RuleResult::INTRODUCTION:
                    applyFalseIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyFalseElimination(rule);
                    break;
            }
            break;
        default:
            throw std::invalid_argument("Invalid LogicOperation");
    }

}


void Deduction::addAssumption(Formula *f)
{
    auto shared = std::make_shared<Node>(f);
    assumptions.push_back(shared);
    conclusions.push_back(shared);
}

void Deduction::applyFalseIntroduction(Rule rule)
{
    applyNegationElimination(Rule(LogicOperation::NOT, RuleResult::ELIMINATION, {rule.getPremises()[0]}));
}



std::vector<std::shared_ptr<Node>>::iterator Deduction::findAssumption(Formula *ruleAssumed)
{

    for (auto assumption = assumptions.begin(); assumption != assumptions.end(); assumption++)
    {
        if (*((assumption)->get()->getFormula()) == *(ruleAssumed))
        {
            return assumption;
        }
    }

    return assumptions.end();
}

void Deduction::print()
{

    std::cout << "Assumptions: [";
    bool first = true;
    std::vector<Formula *> printed;
    for (const auto &assumption: assumptions)
    {
        auto formula = assumption->getFormula();
        if (!findFormulaInVector(printed, formula))
        {
            if (!assumption->isCrossed())
            {
                if (!first)
                {
                    std::cout << ", ";
                } else
                {
                    first = false;
                }
                formula->print();
                printed.push_back(formula);
            }
        }
    }
    std::cout << "]" << std::endl;

    printConclusions();

}

void Deduction::printConclusions()
{
    std::cout << "Conclusions: [";
    bool first = true;
    std::vector<Formula *> printed;
    for (const auto &conclusion: conclusions)
    {
        auto formula = conclusion->getFormula();
        if (!findFormulaInVector(printed, formula))
        {
            if (!first)
            {
                std::cout << ", ";
            } else
            {
                first = false;
            }
            formula->print();
            printed.push_back(formula);
        }

    }
    std::cout << "]" << std::endl << std::endl;
}

std::vector<std::shared_ptr<Node>>::iterator Deduction::findConclusion(const Formula *const ruleAssumed)
{
    for (auto conclusion = conclusions.begin(); conclusion != conclusions.end(); conclusion++)
    {
        if (*((conclusion)->get()->getFormula()) == *(ruleAssumed))
        {
            return conclusion;
        }
    }

    return conclusions.end();
}

std::vector<std::shared_ptr<Node>>::iterator Deduction::findConclusion(const Node *const ruleAssumed)
{
    for (auto conclusion = conclusions.begin(); conclusion != conclusions.end(); conclusion++)
    {
        if (conclusion->get() == ruleAssumed)
        {
            return conclusion;
        }
    }

    return conclusions.end();
}


void Deduction::getNodePointingToConclusion(const Formula *conclusion, Node *&node)
{

    while (node->getNext() != nullptr)
    {
        if (*(node->getNext()->getFormula()) == *conclusion)
        {
            break;
        }
        node = node->getNext();
    }

    if (node->getNext() == nullptr ||
        node->getNext()->getNext() != nullptr)
    {
        throw std::invalid_argument("Invalid conclusion");
    }

    node = node->getNext();
}

char Deduction::getXNotInFormula(const Formula *formula)
{
    std::set<char> free = formula->getFreeVariables();
    for (char c = 'a'; c <= 'z'; c++)
    {
        if (free.find(c) == free.end())
        {
            return c;
        }
    }
    throw std::invalid_argument("No free variables");
}

bool Deduction::findFormulaInVector(std::vector<Formula *> vector1, Formula *pFormula)
{
    return std::any_of(vector1.begin(), vector1.end(), [pFormula](Formula *formula)
    {
        return *formula == *pFormula;
    });
}
