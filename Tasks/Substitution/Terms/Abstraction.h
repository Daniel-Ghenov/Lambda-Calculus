#pragma once
#include "LambdaTerm.h"

class Abstraction: public LambdaTerm {
private:
    LambdaTerm* term;
    char var;
    std::set<char> freeVariables;
    std::set<char> boundVariables;
public:
    Abstraction(LambdaTerm* term, char var);
    Abstraction(const LambdaTerm& term, char var);
    ~Abstraction() override;
    [[nodiscard]] const std::set<char>& getFreeVariables() const override;
    [[nodiscard]] const std::set<char>& getBoundVariables() const override;
    [[nodiscard]] LambdaTerm* clone() const override;
    LambdaTerm *substitute(char var, const LambdaTerm &term) override;
    void print() const override;

private:
    bool isCatching(char var, const LambdaTerm &term);
    char findNotUsedVar(const LambdaTerm& term);
    static isAlpha(char c);
};