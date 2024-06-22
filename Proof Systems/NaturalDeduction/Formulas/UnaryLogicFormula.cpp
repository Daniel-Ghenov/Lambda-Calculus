#include "UnaryLogicFormula.h"


UnaryLogicFormula::UnaryLogicFormula(Formula *operand, LogicOperation op): LogicFormula(op), operand(operand) {

}


Formula *UnaryLogicFormula::clone() const {
    return new UnaryLogicFormula(operand->clone(), operation);
}

Formula *UnaryLogicFormula::getOperand() const {
    return operand.get();
}

LogicOperation UnaryLogicFormula::getOperation() const {
    return operation;
}

std::set<char> UnaryLogicFormula::getFreeVariables() const {
    return operand->getFreeVariables();
}
