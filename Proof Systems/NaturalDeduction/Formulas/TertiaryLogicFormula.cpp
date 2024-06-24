#include <iostream>
#include "TertiaryLogicFormula.h"

std::set<char> TertiaryLogicFormula::getFreeVariables() const {
    std::set<char> result = main->getFreeVariables();
    std::set<char> leftVars = left->getFreeVariables();
    result.insert(leftVars.begin(), leftVars.end());
    std::set<char> rightVars = right->getFreeVariables();
    result.insert(rightVars.begin(), rightVars.end());
    return result;
}

Formula *TertiaryLogicFormula::clone() const {
    return new TertiaryLogicFormula(main->clone(), left->clone(), right->clone());
}

bool TertiaryLogicFormula::operator==(const Formula &other) const {
    if (!LogicFormula::operator==(other)) {
        return false;
    }
    auto *otherTertiary = dynamic_cast<const TertiaryLogicFormula*>(&other);
    if (otherTertiary == nullptr) {
        return false;
    }
    return *main == *otherTertiary->main && *left == *otherTertiary->left && *right == *otherTertiary->right;
}

void TertiaryLogicFormula::print() const {
    main->print();
    std::cout << "[ ";
    left->print();
    std::cout << " -> ";
    right->print();
    std::cout << " ]";
}
