#include "Abstraction.h"
#include <stdexcept>
#include "Variable.h"

const constexpr char MAX_CHAR = 125;

const std::set<char>& Abstraction::getFreeVariables() const {
    return freeVariables;
}

const std::set<char>& Abstraction::getBoundVariables() const {
    return boundVariables;
}

Abstraction::Abstraction(LambdaTerm *term, char var) {
    this->term = term;
    this->var = var;
    this->freeVariables = this->term->getFreeVariables();
    this->boundVariables = this->term->getBoundVariables();
    this->freeVariables.erase(var);
    this->boundVariables.insert(var);
}

Abstraction::Abstraction(const LambdaTerm &term, char var) {
    this->term = term.clone();
    this->var = var;
    this->freeVariables = this->term->getFreeVariables();
    this->boundVariables = this->term->getBoundVariables();
    this->freeVariables.erase(var);
    this->boundVariables.insert(var);
}

LambdaTerm *Abstraction::clone() const {
    return new Abstraction(*term, var);
}

Abstraction::~Abstraction() {
    delete term;
}

LambdaTerm *Abstraction::substitute(char var, const LambdaTerm &term) {
    if (this->var == var) {
        return this;
    }

    char newVar = findNotUsedVar(term);
    auto newTerm = this->term->clone()->substitute(this->var, Variable(newVar));
    newTerm = newTerm->substitute(var, term);
    return new Abstraction(newTerm, newVar);

}

bool Abstraction::isCatching(char var, const LambdaTerm &term) {
    auto ownTermFV = this->term->getFreeVariables();
    auto newTermFV = term.getFreeVariables();
    return ownTermFV.find(var) != ownTermFV.end() && newTermFV.find(this->var) != newTermFV.end();
}

char Abstraction::findNotUsedVar(const LambdaTerm& term) {
    auto otherFV = term.getFreeVariables();
    for(char c = 'a'; c <= 'z'; c++) {
        if (this->freeVariables.find(c) == freeVariables.end() &&
            otherFV.find(c) == otherFV.end()) {
            return c;
        }
    }

    for(char c = 'A'; c <= 'Z'; c++) {
        if (this->freeVariables.find(c) == freeVariables.end() &&
            otherFV.find(c) == otherFV.end()) {
            return c;
        }
    }

    for(char c = 0; c < MAX_CHAR; c++) {
        if (isAlpha(c)) {
            continue;
        }

        if (this->freeVariables.find(c) == freeVariables.end() &&
            otherFV.find(c) == otherFV.end()) {
            return c;
        }
    }
    //TODO: fix this char overflow?
    throw std::length_error("Too many variables used in terms");
}

void Abstraction::print() const {
    std::cout << "(\\";
    std::cout << var;
    std::cout << ".";
    term->print();
    std::cout << ")";
}

int Abstraction::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

