
#include <memory>
#include "Deduction/Deduction.h"
#include "Formulas/Variable.h"
#include "Formulas/BinaryLogicFormula.h"

int main()
{

    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    std::shared_ptr<Variable> a3 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');

    Formula *aAndB = new BinaryLogicFormula(a, b, LogicOperation::AND);
    std::shared_ptr<BinaryLogicFormula> aAndB2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::AND);
    std::shared_ptr<BinaryLogicFormula> aAndB3 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::AND);

    deduction.addAssumption(aAndB);
    deduction.print();

    Rule rule(LogicOperation::AND, RuleResult::ELIMINATION, {aAndB2, a2});

    deduction.applyRule(rule);


    deduction.print();

    Rule rule1(LogicOperation::IMPLIES, RuleResult::INTRODUCTION, {aAndB3, a3});
    deduction.applyRule(rule1);
    deduction.print();


    return 0;
}