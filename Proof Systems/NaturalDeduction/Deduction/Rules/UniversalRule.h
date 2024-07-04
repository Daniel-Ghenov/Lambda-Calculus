#pragma once

#include "Rule.h"

class UniversalRule: public Rule
{
private:
    [[nodiscard]] int getRuleArgumentCountIntroduction() const override;
    [[nodiscard]] int getRuleArgumentCountElimination() const override;

    void applyIntroduction(Deduction &deduction) const override;
    void applyElimination(Deduction &deduction) const override;
public:
    UniversalRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises);

};
