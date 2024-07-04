#pragma once

#include "Rule.h"

class DisjunctionRule : public Rule
{
private:
    [[nodiscard]] int getRuleArgumentCountIntroduction() const override;
    [[nodiscard]] int getRuleArgumentCountElimination() const override;

    void applyIntroduction(Deduction &deduction) const override;
    void applyElimination(Deduction &deduction) const override;

public:
    DisjunctionRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises);

};
