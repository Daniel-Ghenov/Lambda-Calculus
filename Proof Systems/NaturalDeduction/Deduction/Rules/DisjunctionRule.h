#pragma once

#include "Rule.h"

class DisjunctionRule : public Rule
{
private:
    void applyIntroduction(Deduction &deduction) const override;
    void applyElimination(Deduction &deduction) const override;

    static const int argumentCountIntroduction = 2;
    static const int argumentCountElimination = 2;

public:
    DisjunctionRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises);

};
