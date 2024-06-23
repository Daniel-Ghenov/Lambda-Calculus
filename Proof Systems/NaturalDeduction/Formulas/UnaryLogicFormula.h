#pragma once
#include <memory>
#include "LogicFormula.h"

class UnaryLogicFormula : public LogicFormula
{
private:
    std::unique_ptr<Formula> operand;
public:
    explicit UnaryLogicFormula(Formula *operand);
    ~UnaryLogicFormula() override = default;
    [[nodiscard]] Formula *clone() const override;
    [[nodiscard]] std::set<char> getFreeVariables() const override;
    [[nodiscard]] Formula *getOperand() const;
    bool operator==(const Formula& other) const override;
    void print() const override;
};

static const UnaryLogicFormula FALSE = UnaryLogicFormula(nullptr);
