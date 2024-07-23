#pragma once

#include "Rule.h"

class ConjunctionRule : public Rule
{
private:
    void applyIntroduction(Deduction &deduction) const override;
    void applyElimination(Deduction &deduction) const override;

    static const int argumentCountIntroduction = 1;
    static const int argumentCountElimination = 2;
public:
    ConjunctionRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises);

    static std::unique_ptr<ConjunctionRule> createRule(RuleResult result);

private:
    static std::unique_ptr<ConjunctionRule> createIntroductionRule();

    static std::unique_ptr<ConjunctionRule> createEliminationRule();
};
