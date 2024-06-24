
#include <memory>
#include "Deduction/Deduction.h"
#include "Formulas/Variable.h"
#include "Formulas/BinaryLogicFormula.h"
#include "Formulas/UnaryLogicFormula.h"

void test1()
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
}

void test2(){
    Deduction deduction;

    Formula *a = new Variable('A');
    Formula *aa = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');

    Formula *aImpliesB = new BinaryLogicFormula(a, b, LogicOperation::IMPLIES);
    std::shared_ptr<BinaryLogicFormula> aImpliesB2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::IMPLIES);

    deduction.addAssumption(aImpliesB);
    deduction.addAssumption(aa);
    deduction.print();

    Rule rule(LogicOperation::IMPLIES, RuleResult::ELIMINATION, {aImpliesB2});

    deduction.applyRule(rule);


    deduction.print();
}

void test3()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');

    std::shared_ptr<BinaryLogicFormula> aAndB = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::AND);

    deduction.addAssumption(a);
    deduction.addAssumption(b);
    deduction.print();

    Rule rule(LogicOperation::AND, RuleResult::INTRODUCTION, {aAndB});

    deduction.applyRule(rule);


    deduction.print();
}

void test4()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');

    std::shared_ptr<BinaryLogicFormula> aOrB = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR);

    deduction.addAssumption(a);
    deduction.print();

    Rule rule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrB, a2});

    deduction.applyRule(rule);


    deduction.print();
}

void test5()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');
    std::shared_ptr<Variable> b2 = std::make_shared<Variable>('B');

    Formula *aORB = new BinaryLogicFormula(a->clone(), b->clone(), LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrB = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrB2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrB3 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrB4 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR);

    deduction.addAssumption(a);
    deduction.addAssumption(b);
    deduction.addAssumption(aORB);
    deduction.print();

    Rule rule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrB, a2});
    Rule rule2(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrB2, b2});

    deduction.applyRule(rule);
    deduction.print();

    deduction.applyRule(rule2);
    deduction.print();

    Rule rule3(LogicOperation::OR, RuleResult::ELIMINATION, {aOrB3, aOrB4});

    deduction.applyRule(rule3);
    deduction.print();
}

void provingDeMorgan()
{
    Deduction deduction;

    Variable *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    std::shared_ptr<Variable> a3 = std::make_shared<Variable>('A');
    Variable *b = new Variable('B');
    std::shared_ptr<Variable> b2 = std::make_shared<Variable>('B');

    Formula *aOrB = new BinaryLogicFormula(a->clone(), b->clone(), LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrBShared = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrBShared2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR);
    Formula *notAOrB = new UnaryLogicFormula(aOrB->clone());
    std::shared_ptr<UnaryLogicFormula> notAorBShared = std::make_shared<UnaryLogicFormula>(aOrB->clone());
    Formula *notAOrB2 = new UnaryLogicFormula(aOrB->clone());

    deduction.addAssumption(a);
    deduction.addAssumption(notAOrB2);

    Rule rule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrBShared, a2});
    deduction.print();

    deduction.applyRule(rule);
    deduction.print();

    std::shared_ptr<BinaryLogicFormula> notAorBSharedAndAorB = std::make_shared<BinaryLogicFormula>(notAOrB->clone(), aOrB->clone(), LogicOperation::AND);
    Rule rule2(LogicOperation::AND, RuleResult::INTRODUCTION, {notAorBSharedAndAorB});


    deduction.applyRule(rule2);
    deduction.print();

    Rule rule3(LogicOperation::NOT, RuleResult::ELIMINATION, {std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR)});

    deduction.applyRule(rule3);
    deduction.print();

    Rule rule4(LogicOperation::NOT, RuleResult::INTRODUCTION, {std::make_shared<Variable>(a->getVariable())});

    deduction.applyRule(rule4);
    deduction.print();
    deduction.addAssumption(b);
    deduction.addAssumption(notAOrB);

    Rule rule5(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrBShared, b2});

    deduction.applyRule(rule5);
    deduction.print();

    std::shared_ptr<BinaryLogicFormula> notAorBSharedAndAorB2 = std::make_shared<BinaryLogicFormula>(notAOrB->clone(), aOrB->clone(), LogicOperation::AND);
    Rule rule6(LogicOperation::AND, RuleResult::INTRODUCTION, {notAorBSharedAndAorB});


    deduction.applyRule(rule6);
    deduction.print();

    Rule rule7(LogicOperation::NOT, RuleResult::ELIMINATION, {std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR)});

    deduction.applyRule(rule7);
    deduction.print();

    Rule rule8(LogicOperation::NOT, RuleResult::INTRODUCTION, {std::make_shared<Variable>(b->getVariable())});

    deduction.applyRule(rule8);
    deduction.print();

    std::shared_ptr<BinaryLogicFormula> notAAndNotB = std::make_shared<BinaryLogicFormula>(new UnaryLogicFormula(a->clone()), new UnaryLogicFormula(b->clone()), LogicOperation::AND);

    Rule rule9(LogicOperation::AND, RuleResult::INTRODUCTION, {notAAndNotB});

    deduction.applyRule(rule9);
    deduction.print();
}

int main()
{

    provingDeMorgan();

    return 0;
}