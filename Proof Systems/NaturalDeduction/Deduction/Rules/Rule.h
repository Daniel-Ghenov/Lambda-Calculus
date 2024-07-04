
#include <vector>
#include <memory>
#include "../../Formulas/LogicFormula.h"
#include "../Deduction.h"

enum class RuleResult
{
    INTRODUCTION,
    ELIMINATION,
};

class Rule
{
protected:
    LogicOperation type;
    RuleResult result;
    std::vector<std::shared_ptr<Formula>> premises;

    [[nodiscard]] virtual int getRuleArgumentCountIntroduction() const = 0;

    [[nodiscard]] virtual int getRuleArgumentCountElimination() const = 0;

    virtual void applyIntroduction(Deduction &deduction) const = 0;

    virtual void applyElimination(Deduction &deduction) const = 0;
    Rule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises);

public:
    [[nodiscard]] int getRuleArgumentCount() const;

    [[nodiscard]] LogicOperation getType() const;
    [[nodiscard]] RuleResult getResult() const;
    [[nodiscard]] std::vector<std::shared_ptr<Formula>> getPremises() const;

    void apply(Deduction &d) const;

};
