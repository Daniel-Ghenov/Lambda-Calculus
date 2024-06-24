#include <iostream>
#include "BinaryLogicFormula.h"

BinaryLogicFormula::BinaryLogicFormula(Formula *left, Formula *right, LogicOperation op): LogicFormula(op, FormulaType::BINARY_LOGIC), leftOperand(left), rightOperand(right) {}

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

bool BinaryLogicFormula::operator==(const Formula &other) const {
    if (!LogicFormula::operator==(other)) {
        return false;
    }
    auto *otherBinary = dynamic_cast<const BinaryLogicFormula*>(&other);
    if (otherBinary == nullptr) {
        return false;
    }
    if (operation == LogicOperation::AND && otherBinary->operation == LogicOperation::AND) {
        return andEquals(otherBinary);
    }
    return operation == otherBinary->operation && *leftOperand == *otherBinary->leftOperand && *rightOperand == *otherBinary->rightOperand;
}

void BinaryLogicFormula::print() const {
    std::cout << "(";
    leftOperand->print();
    switch (operation) {
        case LogicOperation::AND:
            std::cout << " & ";
            break;
        case LogicOperation::OR:
            std::cout << " | ";
            break;
        case LogicOperation::IMPLIES:
            std::cout << " -> ";
            break;
        case LogicOperation::NOT:
            break;
        case LogicOperation::BIDIRECTIONAL_IMPLIES:
            break;
        case LogicOperation::FOR_ALL:
            break;
        case LogicOperation::EXISTS:
            break;
    }
    rightOperand->print();
    std::cout << ")";
}

bool BinaryLogicFormula::andEquals(const BinaryLogicFormula *pFormula) const {
    return (*leftOperand == *pFormula->leftOperand && *rightOperand == *pFormula->rightOperand) ||
           (*leftOperand == *pFormula->rightOperand && *rightOperand == *pFormula->leftOperand);
}

