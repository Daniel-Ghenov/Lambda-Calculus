#pragma once

#include "Rule.h"

class ImplicationRule : public Rule
{
private:
    void applyIntroduction(Deduction &deduction) const override;
    void applyElimination(Deduction &deduction) const override;

    static const int argumentCountIntroduction = 2;
    static const int argumentCountElimination = 1;
public:
    explicit ImplicationRule(std::vector<std::shared_ptr<Formula>> &&premises);
    ImplicationRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises, std::vector<char>&& markers);
};
