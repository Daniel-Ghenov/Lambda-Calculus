#include <stdexcept>
#include <iostream>
#include "UnaryLogicFormula.h"


UnaryLogicFormula::UnaryLogicFormula(Formula *operand): LogicFormula(LogicOperation::NOT, FormulaType::UNARY_LOGIC), operand(operand) {

}


Formula *UnaryLogicFormula::clone() const {
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
    return operation == otherUnary->operation && *operand == *otherUnary->operand;
}

void UnaryLogicFormula::print() const {
    std::cout << logicOperationToString(operation) << "(";
    operand->print();
    std::cout << ")";
}
