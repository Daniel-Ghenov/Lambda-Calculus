#pragma once
#include <string>
#include <memory>
#include "Formula.h"

class FormulaFactory
{
private:
    FormulaFactory() = default;
public:
    static std::shared_ptr<Formula> createFormula(std::string &formulaString);
};
