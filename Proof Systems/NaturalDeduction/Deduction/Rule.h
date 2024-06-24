
#include <vector>
#include <memory>
#include "../Formulas/LogicFormula.h"

enum class RuleResult
{
    INTRODUCTION,
    ELIMINATION,
};




class Rule {
private:
    LogicOperation type;
    RuleResult result;
    std::vector<std::shared_ptr<Formula>> premises;

    [[nodiscard]] int getRuleArgumentCountIntroduction() const;
    [[nodiscard]] int getRuleArgumentCountElimination() const;
public:
    [[nodiscard]] int getRuleArgumentCount() const;
    Rule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>>&& premises);

    [[nodiscard]] LogicOperation getType() const;
    [[nodiscard]] RuleResult getResult() const;
    [[nodiscard]] std::vector<std::shared_ptr<Formula>> getPremises() const;

};
