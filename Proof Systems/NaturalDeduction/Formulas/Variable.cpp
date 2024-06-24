#include <iostream>
#include "Variable.h"

Variable::Variable(char c): Formula(FormulaType::VARIABLE), var(c), freeVariables({c}) { }

Formula *Variable::clone() const {
    return new Variable(this->var);
}

std::set<char> Variable::getFreeVariables() const {
    return freeVariables;
}

bool Variable::operator==(const Formula &other) const {
    if (!Formula::operator==(other)) {
        return false;
    }
    const auto &otherVar = dynamic_cast<const Variable &>(other);
    return var == otherVar.var;
}

void Variable::print() const {
    std::cout << var;
}
