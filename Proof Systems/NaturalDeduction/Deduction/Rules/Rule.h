#pragma once
#include <vector>
#include <memory>
#include "../../Formulas/LogicFormula.h"
#include "../Deduction.h"

enum class RuleResult
{
    INTRODUCTION,
    ELIMINATION,
};

RuleResult ruleResultFromString(const std::string &s);

class Rule
{
protected:

    LogicOperation type;
    RuleResult result;
    std::vector<std::shared_ptr<Formula>> premises;
    std::vector<char> markers = {};

    virtual void applyIntroduction(Deduction &deduction) const = 0;
    virtual void applyElimination(Deduction &deduction) const = 0;
    Rule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises, int permiseSize);
    Rule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises, std::vector<char>&& markers, int permiseSize);

    static int getArgumentCount(RuleResult, int introductionCount, int eliminationCount);

public:

    [[nodiscard]] LogicOperation getType() const;
    [[nodiscard]] RuleResult getResult() const;
    [[nodiscard]] std::vector<std::shared_ptr<Formula>> getPremises() const;

    void apply(Deduction &d) const;

};
