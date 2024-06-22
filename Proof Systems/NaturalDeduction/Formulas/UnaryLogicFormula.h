#pragma once
#include <memory>
#include "LogicFormula.h"

class UnaryLogicFormula : public LogicFormula
{
private:
    std::unique_ptr<Formula> operand;
public:
    explicit UnaryLogicFormula(Formula *operand, LogicOperation op);
    ~UnaryLogicFormula() override = default;
    [[nodiscard]] Formula *clone() const override;
    [[nodiscard]] std::set<char> getFreeVariables() const override;
    [[nodiscard]] Formula *getOperand() const;
    [[nodiscard]] LogicOperation getOperation() const;
};
