#pragma once

#include "Rule.h"

class FalseRule: public Rule
{
private:
    void applyIntroduction(Deduction &deduction) const override;
    void applyElimination(Deduction &deduction) const override;

    static const int argumentCountIntroduction = 1;
    static const int argumentCountElimination = 1;
public:
    FalseRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises);
};
