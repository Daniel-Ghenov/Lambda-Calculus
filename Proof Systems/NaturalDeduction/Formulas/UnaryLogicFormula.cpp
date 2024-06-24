#include <stdexcept>
#include <iostream>
#include "UnaryLogicFormula.h"
 const UnaryLogicFormula UnaryLogicFormula::FALSE = UnaryLogicFormula(nullptr);

UnaryLogicFormula::UnaryLogicFormula(Formula *operand): LogicFormula(LogicOperation::NOT, FormulaType::UNARY_LOGIC), operand(operand) {

}


Formula *UnaryLogicFormula::clone() const {
    if (operand == nullptr) {
        return new UnaryLogicFormula(nullptr);
    }
    return new UnaryLogicFormula(operand->clone());
}

Formula *UnaryLogicFormula::getOperand() const {
    return operand.get();
}

std::set<char> UnaryLogicFormula::getFreeVariables() const {
    return operand->getFreeVariables();
}

bool UnaryLogicFormula::operator==(const Formula &other) const {
    if (!LogicFormula::operator==(other)) {
        return false;
    }
    auto *otherUnary = dynamic_cast<const UnaryLogicFormula*>(&other);
    if (otherUnary == nullptr) {
        return false;
    }
    if (operand == nullptr && otherUnary->operand == nullptr) {
        return true;
    }
    if (operand == nullptr || otherUnary->operand == nullptr) {
        return false;
    }
    return operation == otherUnary->operation && *operand == *otherUnary->operand;
}

void UnaryLogicFormula::print() const {
    if (operand == nullptr) {
        std::cout << "FALSE";
        return;
    }
    std::cout << logicOperationToString(operation) << "(";
    operand->print();
    std::cout << ")";
}
