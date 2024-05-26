#pragma once
#include <set>

class LambdaTerm {
public:
    virtual ~LambdaTerm() = default;
    [[nodiscard]] virtual const std::set<char>& getFreeVariables() const = 0;
    [[nodiscard]] virtual const std::set<char>& getBoundVariables() const = 0;
    [[nodiscard]] virtual LambdaTerm* clone() const = 0 ;
    [[nodiscard]] virtual LambdaTerm* substitute(char var, const LambdaTerm& term) = 0;
    virtual void print() const = 0;
};

