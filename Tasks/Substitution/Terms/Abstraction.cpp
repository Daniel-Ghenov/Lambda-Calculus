#include "Abstraction.h"

const std::set<char>& Abstraction::getFreeVariables() const {
    return freeVariables;
}

const std::set<char>& Abstraction::getBoundVariables() const {
    return boundVariables;
}

Abstraction::Abstraction(const LambdaTerm &term, char var) {
    this->term = term.clone();
    this->var = var;
    this->freeVariables = term.getFreeVariables();
    this->boundVariables = term.getBoundVariables();
    this->freeVariables.erase(var);
    this->boundVariables.insert(var);
}

LambdaTerm *Abstraction::clone() const {
    return new Abstraction(*term, var);
}

Abstraction::~Abstraction() {
    delete term;
}