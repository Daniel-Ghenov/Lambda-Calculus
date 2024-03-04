#include "Variable.h"

const std::set<char>& Variable::getFreeVariables() const {
    return freeVariables;
}

const std::set<char>& Variable::getBoundVariables() const {
    return boundVariables;
}

LambdaTerm *Variable::clone() const {
    return new Variable(this->var);
}

Variable::Variable(char c): var(c) {
    this->freeVariables = std::set<char>({c});
    this->boundVariables = std::set<char>();
}

LambdaTerm *Variable::substitute(char var, const LambdaTerm &term) {
    if (var != this->var) {
        return this;
    }
    return term.clone();
}
