#pragma once
#include <set>

class LambdaTerm {
public:
    virtual ~LambdaTerm() = default;
    [[nodiscard]] virtual const std::set<char>& getFreeVariables() const = 0;
    [[nodiscard]] virtual const std::set<char>& getBoundVariables() const = 0;
    [[nodiscard]] virtual LambdaTerm* clone() const = 0 ;
};

