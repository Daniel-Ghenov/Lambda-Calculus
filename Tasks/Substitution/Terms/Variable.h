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
    [[nodiscard]] const std::set<char>& getFreeVariables() const override;
    [[nodiscard]] const std::set<char>& getBoundVariables() const override;
    [[nodiscard]] LambdaTerm* clone() const override;
};

