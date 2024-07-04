#pragma once

#include <set>

enum class FormulaType
{
    VARIABLE,
    UNARY_LOGIC,
    BINARY_LOGIC,
    TERTIARY_LOGIC,
    SUBSTITUTION,
};

class Formula
{
private:
    FormulaType type;
public:
    explicit Formula(FormulaType type) : type(type)
    {}

    virtual ~Formula() = default;

    [[nodiscard]] FormulaType getType() const
    { return type; }

    [[nodiscard]] virtual Formula *clone() const = 0;

    [[nodiscard]] virtual std::set<char> getFreeVariables() const = 0;

    virtual bool operator==(const Formula &other) const = 0;

    virtual void print() const = 0;
};
