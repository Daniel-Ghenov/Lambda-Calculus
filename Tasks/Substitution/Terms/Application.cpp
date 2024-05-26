#include "Application.h"

Application::~Application() {
    delete term1;
    delete term2;
}

Application::Application(const LambdaTerm& term1, const LambdaTerm& term2) {
    this->term1 = term1.clone();
    this->term2 = term2.clone();
    this->boundVariables = term1.getBoundVariables();
    this->boundVariables.insert(term2.getBoundVariables().begin(), term2.getBoundVariables().end());
    this->freeVariables = term1.getFreeVariables();
    this->freeVariables.insert(term2.getFreeVariables().begin(), term2.getFreeVariables().end());
}


LambdaTerm *Application::clone() const {
    return new Application(*term1, *term2);
}

const std::set<char> &Application::getBoundVariables() const {
    return boundVariables;
}

const std::set<char> &Application::getFreeVariables() const {
    return freeVariables;
}

LambdaTerm *Application::substitute(char var, const LambdaTerm &term) {
    term1 = term1->substitute(var, term);
    term2 = term2->substitute(var, term);
    return this;
}

void Application::print() const {
    std::cout << "(";
    term1->print();
    std::cout << " ";
    term2->print();
    std::cout << ")";
}
