#pragma once
#include "LambdaTerm.h"

class Abstraction: public LambdaTerm {
private:
    LambdaTerm* term;
    char var;
    std::set<char> freeVariables;
    std::set<char> boundVariables;
public:
    Abstraction(const LambdaTerm& term, char var);
    ~Abstraction() override;
    const std::set<char>& getFreeVariables() const override;
    const std::set<char>& getBoundVariables() const override;
    LambdaTerm* clone() const override;
};