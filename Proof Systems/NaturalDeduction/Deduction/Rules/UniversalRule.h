#pragma once

#include "Rule.h"

class UniversalRule: public Rule
{
private:
    void applyIntroduction(Deduction &deduction) const override;
    void applyElimination(Deduction &deduction) const override;

    static const int argumentCountIntroduction = 1;
    static const int argumentCountElimination = 2;
public:
    UniversalRule(RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises);

    static std::unique_ptr<UniversalRule> createRule(RuleResult result);

private:
    static std::unique_ptr<UniversalRule> createIntroductionRule();

    static std::unique_ptr<UniversalRule> createEliminationRule();
};
