#pragma once

#include <memory>
#include "LogicFormula.h"

class BinaryLogicFormula : public LogicFormula
{
private:
    std::unique_ptr<Formula> leftOperand;
    std::unique_ptr<Formula> rightOperand;
public:
    explicit BinaryLogicFormula(Formula *left, Formula *right, LogicOperation op);
    ~BinaryLogicFormula() override = default;
    [[nodiscard]] Formula *clone() const override;
    [[nodiscard]] std::set<char> getFreeVariables() const override;
    [[nodiscard]] Formula *getLeftOperand() const;
    [[nodiscard]] Formula *getRightOperand() const;
    [[nodiscard]] LogicOperation getOperation() const;

};
