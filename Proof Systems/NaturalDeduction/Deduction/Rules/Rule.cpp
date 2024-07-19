#include <stdexcept>
#include <utility>
#include "Rule.h"


Rule::Rule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises, int premiseSize) : type(type),
                                                                                                       result(result),
                                                                                                       premises(std::move(premises))
{
    if (this->premises.size() != premiseSize)
    {
        throw std::invalid_argument("Invalid number of premises");
    }
}

Rule::Rule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises,
           std::vector<char>&& markers, int premiseSize): type(type),
                                                          result(result),
                                                          premises(std::move(premises)),
                                                          markers(std::move(markers))
{
    if (this->premises.size() != premiseSize)
    {
        throw std::invalid_argument("Invalid number of premises");
    }
}

LogicOperation Rule::getType() const
{
    return type;
}

RuleResult Rule::getResult() const
{
    return result;
}

std::vector<std::shared_ptr<Formula>> Rule::getPremises() const
{
    return premises;
}

void Rule::apply(Deduction &d) const
{
    switch (this->result)
    {
        case RuleResult::INTRODUCTION:
            applyIntroduction(d);
            break;
        case RuleResult::ELIMINATION:
            applyElimination(d);
            break;
        default:
            throw std::invalid_argument("Invalid RuleResult");
    }
}

int Rule::getArgumentCount(RuleResult result, int introductionCount, int eliminationCount)
{
    switch (result)
    {
        case RuleResult::INTRODUCTION:
            return introductionCount;
        case RuleResult::ELIMINATION:
            return eliminationCount;
        default:
            throw std::invalid_argument("Invalid RuleResult");
    }
}
