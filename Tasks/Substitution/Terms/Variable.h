#pragma once
#include <iostream>
#include "LambdaTerm.h"

class Variable: public LambdaTerm {
private:
    char var;
    std::set<char> freeVariables;
    std::set<char> boundVariables;
public:
    explicit Variable(char c);
    ~Variable() override = default;
    [[nodiscard]] const std::set<char>& getFreeVariables() const override;
    [[nodiscard]] const std::set<char>& getBoundVariables() const override;
    [[nodiscard]] LambdaTerm* clone() const override;

    LambdaTerm *substitute(char var, const LambdaTerm &term) override;
    void print() const override;
};

