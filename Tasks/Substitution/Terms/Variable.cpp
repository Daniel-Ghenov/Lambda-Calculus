#include "Variable.h"

const std::set<char>& Variable::getFreeVariables() const {
    return freeVariables;
}

const std::set<char>& Variable::getBoundVariables() const {
    return boundVariables;
}

LambdaTerm *Variable::clone() const {
    return new Variable(this->c);
}

Variable::Variable(char c): c(c) {
    this->freeVariables = std::set<char>({c});
    this->boundVariables = std::set<char>();
}