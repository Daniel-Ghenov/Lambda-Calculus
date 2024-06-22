#include "Variable.h"

Variable::Variable(char c): var(c), freeVariables({c}) { }

Formula *Variable::clone() const {
    return new Variable(this->var);
}

std::set<char> Variable::getFreeVariables() const {
    return freeVariables;
}
