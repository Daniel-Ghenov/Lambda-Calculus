cmake_minimum_required(VERSION 3.10)
project(Substitution VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(NaturalDeduction
        main.cpp
        Formulas/Variable.cpp
        Formulas/Variable.h
        Formulas/UnaryLogicFormula.cpp
        Formulas/UnaryLogicFormula.h
        Formulas/BinaryLogicFormula.cpp
        Formulas/BinaryLogicFormula.h
        Formulas/Formula.cpp
        Formulas/Formula.h
        Deduction/Deduction.cpp
        Deduction/Deduction.h
        Formulas/LogicFormula.cpp
        Formulas/LogicFormula.h
        Deduction/Node.h
        Deduction/Node.cpp
        Deduction/Rules/Rule.h
        Deduction/Rules/Rule.cpp
        Formulas/TertiaryLogicFormula.h
        Formulas/TertiaryLogicFormula.cpp
        Deduction/Rules/DisjunctionRule.h
        Deduction/Rules/DisjunctionRule.cpp
        Deduction/Rules/ConjunctionRule.h
        Deduction/Rules/ConjunctionRule.cpp
        Deduction/Rules/ImplicationRule.h
        Deduction/Rules/ImplicationRule.cpp
        Deduction/Rules/NegationRule.h
        Deduction/Rules/NegationRule.cpp
        Deduction/Rules/ExistentialRule.h
        Deduction/Rules/ExistentialRule.cpp
        Deduction/Rules/UniversalRule.h
        Deduction/Rules/UniversalRule.cpp
        Deduction/Rules/FalseRule.h
        Deduction/Rules/FalseRule.cpp
        Deduction/Rules/RuleFactory.h
        Deduction/Rules/RuleFactory.cpp
        Formulas/FormulaFactory.h
        Formulas/FormulaFactory.cpp
        Deduction/DeductionController.h
        Deduction/DeductionController.cpp)