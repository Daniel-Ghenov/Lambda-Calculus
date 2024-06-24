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
        Deduction/Rule.h
        Deduction/Rule.cpp
        Formulas/SubstitutionFormula.h
        Formulas/SubstitutionFormula.cpp
        Formulas/TertiaryLogicFormula.h
        Formulas/TertiaryLogicFormula.cpp)