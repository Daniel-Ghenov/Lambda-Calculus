#pragma once

#include "Rule.h"

class ImplicationRule : public Rule
{
private:
    [[nodiscard]] int getRuleArgumentCountIntroduction() const override;
    [[nodiscard]] int getRuleArgumentCountElimination() const override;

    void applyIntroduction(Deduction &deduction) const override;
    void applyElimination(Deduction &deduction) const override;

public:
    ImplicationRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises);

};
