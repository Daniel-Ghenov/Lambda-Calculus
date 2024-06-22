#pragma once
#include <set>

class Formula
{
public:
    virtual ~Formula() = default;

    [[nodiscard]] virtual Formula* clone() const = 0;
    [[nodiscard]] virtual std::set<char> getFreeVariables() const = 0;
};
