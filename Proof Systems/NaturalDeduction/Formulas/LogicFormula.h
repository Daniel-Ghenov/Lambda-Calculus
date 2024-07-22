#pragma once

#include <string>
#include "Formula.h"

enum class LogicOperation
{
    AND,
    OR,
    IMPLIES,
    NOT,
    BIDIRECTIONAL_IMPLIES,
    FOR_EACH,
    EXISTS,
    SUBSTITUTION,
    FALSE
};

std::string logicOperationToString(LogicOperation op);
LogicOperation logicOperationFromString(const std::string_view &str);

class LogicFormula : public Formula
{
protected:
    LogicOperation operation;
public:
    explicit LogicFormula(LogicOperation op, FormulaType type) : operation(op), Formula(type)
    {}

    ~LogicFormula() override = default;

    [[nodiscard]] Formula *clone() const override = 0;

    [[nodiscard]] std::set<char> getFreeVariables() const override = 0;

    [[nodiscard]] LogicOperation getOperation() const
    { return operation; }
};
