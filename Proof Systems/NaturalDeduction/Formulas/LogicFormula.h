#pragma once
#include "Formula.h"

enum class LogicOperation
{
    AND,
    OR,
    IMPLIES,
    NOT,
    BIDIRECTIONAL_IMPLIES,
    FOR_ALL,
    EXISTS
};

class LogicFormula: public Formula
{
protected:
    LogicOperation operation;
public:
    explicit LogicFormula(LogicOperation op) : operation(op) {}
    ~LogicFormula() override = default;
    [[nodiscard]] Formula* clone() const override = 0;
    [[nodiscard]] std::set<char> getFreeVariables() const override = 0;
};
