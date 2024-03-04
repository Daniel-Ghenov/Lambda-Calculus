#pragma once
#include "LambdaTerm.h"

class Variable: public LambdaTerm {
private:
    char c;
    std::set<char> freeVariables;
    std::set<char> boundVariables;
public:
    explicit Variable(char c);
    ~Variable() override = default;
    const std::set<char>& getFreeVariables() const override;
    const std::set<char>& getBoundVariables() const override;
    LambdaTerm* clone() const override;
};

