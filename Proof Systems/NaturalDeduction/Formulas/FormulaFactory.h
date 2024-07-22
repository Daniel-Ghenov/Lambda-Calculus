#pragma once
#include <string>
#include <memory>
#include "Formula.h"
#include "LogicFormula.h"

class FormulaFactory
{
private:
    FormulaFactory() = default;
public:
    static Formula* createFormula(const std::string_view& formulaString);
    static Formula* createFormula(std::istream& in);

private:
    static int findNextOperation(const std::string_view &view);

    static Formula* createTertiaryFormula(Formula *pFormula, std::string_view view);
};
