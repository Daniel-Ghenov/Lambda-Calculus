#pragma once

#include <memory>
#include "Formula.h"

class SubstitutionFormula : public Formula
{
private:
    std::unique_ptr<Formula> main;
    std::unique_ptr<Formula> from;
    std::unique_ptr<Formula> to;
public:
    SubstitutionFormula(Formula *main, Formula *from, Formula *to);

    ~SubstitutionFormula() override = default;

    [[nodiscard]] Formula *clone() const override;

    [[nodiscard]] std::set<char> getFreeVariables() const override;

    bool operator==(const Formula &other) const override;

    void print() const override;

    [[nodiscard]] Formula *getMain() const;

    [[nodiscard]] Formula *getFrom() const;

    [[nodiscard]] Formula *getTo() const;

};
