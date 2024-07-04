#pragma once

#include <memory>
#include "LogicFormula.h"

class TertiaryLogicFormula : public LogicFormula
{
private:
    std::unique_ptr<Formula> main;
    std::unique_ptr<Formula> left;
    std::unique_ptr<Formula> right;

public:
    TertiaryLogicFormula(Formula *main, Formula *left, Formula *right) : LogicFormula(LogicOperation::SUBSTITUTION,
                                                                                      FormulaType::TERTIARY_LOGIC),
                                                                         main(main), left(left), right(right)
    {}

    ~TertiaryLogicFormula() override = default;

    [[nodiscard]] Formula *clone() const override;

    [[nodiscard]] std::set<char> getFreeVariables() const override;

    [[nodiscard]] Formula *getMain() const
    { return main.get(); }

    [[nodiscard]] Formula *getLeft() const
    { return left.get(); }

    [[nodiscard]] Formula *getRight() const
    { return right.get(); }

    void print() const override;

    bool operator==(const Formula &other) const override;

};
