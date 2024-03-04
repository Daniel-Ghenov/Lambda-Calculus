#pragma once
#include "LambdaTerm.h"

class Application: public LambdaTerm {
private:
    LambdaTerm* term1;
    LambdaTerm* term2;
    std::set<char> freeVariables;
    std::set<char> boundVariables;
public:
    Application(const LambdaTerm& term1, const LambdaTerm& term2);
    ~Application() override;
    [[nodiscard]] const std::set<char> &getFreeVariables() const override;
    [[nodiscard]] const std::set<char> &getBoundVariables() const override;
    [[nodiscard]] LambdaTerm *clone() const override;

    LambdaTerm *substitute(char var, const LambdaTerm &term) override;
};
