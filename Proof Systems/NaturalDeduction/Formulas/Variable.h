#pragma once
#include "Formula.h"

class Variable : public Formula
{
private:
    char var;
    std::set<char> freeVariables;
public:
    explicit Variable(char c);
    ~Variable() override = default;
    [[nodiscard]] Formula* clone() const override;
    [[nodiscard]] std::set<char> getFreeVariables() const override;
    [[nodiscard]] char getVariable() const { return var; }
    bool operator==(const Formula& other) const override;
    void print() const override;
};

