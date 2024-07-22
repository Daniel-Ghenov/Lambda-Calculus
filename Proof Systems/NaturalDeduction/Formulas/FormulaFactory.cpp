#include <stdexcept>
#include "FormulaFactory.h"
#include "UnaryLogicFormula.h"
#include "BinaryLogicFormula.h"
#include "Variable.h"
#include "TertiaryLogicFormula.h"


Formula* FormulaFactory::createFormula(const std::string_view &formulaString)
{
    if (formulaString.empty())
    {
        return nullptr;
    }

    if (formulaString[0] == '!')
    {
        return new UnaryLogicFormula(createFormula(formulaString.substr(1)));
    }

    if (formulaString[0] == '(')
    {

        if (formulaString[1] == '!')
        {
            return new UnaryLogicFormula(createFormula(formulaString.substr(2)));
        }

        int pos = findNextOperation(formulaString.substr(1));
        if (pos == -1)
        {
            throw std::invalid_argument("Invalid formula");
        }

        char betweenOps = formulaString[pos];
        Formula* left = createFormula(formulaString.substr(1, pos - 1));
        if (betweenOps == '[')
        {
            return createTertiaryFormula(left, formulaString.substr(pos + 1, formulaString.size() - pos - 3));
        }
        LogicOperation operation = logicOperationFromString(formulaString.substr(pos));
        size_t opLen = logicOperationToString(operation).size();

        Formula* right = createFormula(formulaString.substr(pos + opLen, formulaString.size() - pos - opLen - 1));
        return new BinaryLogicFormula(left, right, operation);
    }

    if (formulaString == "FALSE")
    {
        return UnaryLogicFormula::getFalse();
    }

    if (isalnum(formulaString[0]))
    {
        return new Variable(formulaString[0]);
    }

    throw std::invalid_argument("Invalid formula");
}

int FormulaFactory::findNextOperation(const std::string_view &view)
{
    if (view[0] != '(')
    {
        return 2;
    }

    int brackets = 0;
    for (int i = 0; i < view.size(); i++)
    {
        if (view[i] == '(')
        {
            brackets++;
        }
        if (view[i] == ')')
        {
            brackets--;
        }
        if (brackets == 0)
        {
            return i + 2;
        }
    }
    return -1;
}

Formula* FormulaFactory::createTertiaryFormula(Formula *pFormula, std::string_view view)
{
    if (view[0] == '(')
    {
        int pos = findNextOperation(view.substr(1));
        if (pos == -1)
        {
            throw std::invalid_argument("Invalid formula");
        }

        Formula* left = createFormula(view.substr(1, pos - 1));


        Formula* right = createFormula(view.substr(pos + 3, view.size() - pos - 4));
        return new TertiaryLogicFormula(pFormula, left, right);
    }
    Formula* var = new Variable(view[0]);
    Formula* right = createFormula(view.substr(3, view.size() - 3));
    return new TertiaryLogicFormula(pFormula, var, right);
}
