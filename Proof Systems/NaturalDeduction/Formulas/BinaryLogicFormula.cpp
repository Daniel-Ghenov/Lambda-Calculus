#include "BinaryLogicFormula.h"

BinaryLogicFormula::BinaryLogicFormula(Formula *left, Formula *right, LogicOperation op): LogicFormula(op), leftOperand(left), rightOperand(right) {}

Formula *BinaryLogicFormula::clone() const {
    return new BinaryLogicFormula(leftOperand->clone(), rightOperand->clone(), operation);
}

std::set<char> BinaryLogicFormula::getFreeVariables() const {
    std::set<char> first = leftOperand->getFreeVariables();
    std::set<char> second = rightOperand->getFreeVariables();
    first.insert(second.begin(), second.end());
    return first;
}

Formula *BinaryLogicFormula::getLeftOperand() const {
    return leftOperand.get();
}

Formula *BinaryLogicFormula::getRightOperand() const {
    return rightOperand.get();
}

LogicOperation BinaryLogicFormula::getOperation() const {
    return operation;
}

