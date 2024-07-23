
#include <memory>
#include <iostream>
#include "Deduction/Deduction.h"
#include "Formulas/Variable.h"
#include "Formulas/BinaryLogicFormula.h"
#include "Formulas/UnaryLogicFormula.h"
#include "Formulas/TertiaryLogicFormula.h"
#include "Deduction/Rules/RuleFactory.h"
#include "Formulas/FormulaFactory.h"
#include "Deduction/DeductionController.h"

void test1()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    std::shared_ptr<Variable> a3 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');

    Formula *aAndB = new BinaryLogicFormula(a, b, LogicOperation::AND);
    std::shared_ptr<BinaryLogicFormula> aAndB2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                      LogicOperation::AND);
    std::shared_ptr<BinaryLogicFormula> aAndB3 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                      LogicOperation::AND);

    deduction.addAssumption(aAndB);
    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::AND, RuleResult::ELIMINATION, {aAndB2, a2});

    rule->apply(deduction);


    deduction.print();

    std::shared_ptr<Rule> rule1 = RuleFactory::createRule(LogicOperation::IMPLIES, RuleResult::INTRODUCTION, {aAndB3, a3});
    rule1->apply(deduction);
    deduction.print();
}

void test2()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    Formula *aa = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');

    Formula *aImpliesB = new BinaryLogicFormula(a, b, LogicOperation::IMPLIES);
    std::shared_ptr<BinaryLogicFormula> aImpliesB2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                          LogicOperation::IMPLIES);

    deduction.addAssumption(aImpliesB);
    deduction.addAssumption(aa);
    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::IMPLIES, RuleResult::ELIMINATION, {aImpliesB2});

    rule->apply(deduction);


    deduction.print();
}

void test3()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');

    std::shared_ptr<BinaryLogicFormula> aAndB = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                     LogicOperation::AND);

    deduction.addAssumption(a);
    deduction.addAssumption(b);
    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::AND, RuleResult::INTRODUCTION, {aAndB});

    rule->apply(deduction);


    deduction.print();
}

void test4()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *b = new Variable('B');

    std::shared_ptr<BinaryLogicFormula> aOrB = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                    LogicOperation::OR);

    deduction.addAssumption(a);
    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrB, a2});

    rule->apply(deduction);


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
    std::shared_ptr<BinaryLogicFormula> aOrB = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                    LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrB2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                     LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrB3 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                     LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrB4 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                     LogicOperation::OR);

    deduction.addAssumption(a);
    deduction.addAssumption(b);
    deduction.addAssumption(aORB);
    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrB, a2});
    std::shared_ptr<Rule> rule2 = RuleFactory::createRule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrB2, b2});

    rule->apply(deduction);
    deduction.print();

    rule2->apply(deduction);
    deduction.print();

    std::shared_ptr<Rule> rule3 = RuleFactory::createRule(LogicOperation::OR, RuleResult::ELIMINATION, {aOrB3, aOrB4});

    rule3->apply(deduction);
    deduction.print();
}

void test6()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *x = new Variable('x');
    std::shared_ptr<Variable> x2 = std::make_shared<Variable>('x');

    Formula *forEachx = new BinaryLogicFormula(x->clone(), a->clone(), LogicOperation::FOR_EACH);

    deduction.addAssumption(a);

    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::FOR_EACH, RuleResult::INTRODUCTION, {a2});

    rule->apply(deduction);
    deduction.print();
}

void test7()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *t = new Variable('t');
    std::shared_ptr<Variable> t2 = std::make_shared<Variable>('t');

    Formula *forEachx = new BinaryLogicFormula(new Variable('x'), a->clone(), LogicOperation::FOR_EACH);
    std::shared_ptr<BinaryLogicFormula> forEachx2 = std::make_shared<BinaryLogicFormula>(new Variable('x'), a->clone(),
                                                                                         LogicOperation::FOR_EACH);

    deduction.addAssumption(t);
    deduction.addAssumption(forEachx);

    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::FOR_EACH, RuleResult::ELIMINATION, {forEachx2, t2});

    rule->apply(deduction);
    deduction.print();
}

void test8()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *x = new Variable('x');
    std::shared_ptr<Variable> x2 = std::make_shared<Variable>('x');
    Formula *t = new Variable('t');
    std::shared_ptr<Variable> t2 = std::make_shared<Variable>('t');

    Formula *aSubstitute = new TertiaryLogicFormula(a->clone(), x->clone(), t->clone());
    std::shared_ptr<TertiaryLogicFormula> aSubstitute2 = std::make_shared<TertiaryLogicFormula>(a->clone(), x->clone(),
                                                                                                t->clone());

    deduction.addAssumption(t);
    deduction.addAssumption(aSubstitute);

    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::EXISTS, RuleResult::INTRODUCTION, {aSubstitute2, t2});

    rule->apply(deduction);
    deduction.print();
}

void test9()
{
    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');
    Formula *x = new Variable('x');
    std::shared_ptr<Variable> x2 = std::make_shared<Variable>('x');
    Formula *b = new Variable('B');
    std::shared_ptr<Variable> b2 = std::make_shared<Variable>('B');

    Formula *existsA = new BinaryLogicFormula(x->clone(), a->clone(), LogicOperation::EXISTS);
    std::shared_ptr<BinaryLogicFormula> existsA2 = std::make_shared<BinaryLogicFormula>(x->clone(), a->clone(),
                                                                                        LogicOperation::EXISTS);

    Formula *aOrB = new BinaryLogicFormula(a->clone(), b->clone(), LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrB2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                     LogicOperation::OR);

    deduction.addAssumption(a);
    deduction.addAssumption(existsA);

    deduction.print();

    std::shared_ptr<Rule> rule1 = RuleFactory::createRule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrB2, a2});
    rule1->apply(deduction);
    deduction.print();

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::EXISTS, RuleResult::ELIMINATION, {existsA2, aOrB2});

    rule->apply(deduction);
    deduction.print();
}

void test10()
{

    Deduction deduction;

    Formula *a = new Variable('A');
    std::shared_ptr<Variable> a2 = std::make_shared<Variable>('A');

    Formula *falseFormula = UnaryLogicFormula::getFalse();

    deduction.addAssumption(falseFormula);

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::FALSE, RuleResult::ELIMINATION, {a2});

    rule->apply(deduction);
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
    std::shared_ptr<BinaryLogicFormula> aOrBShared = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                          LogicOperation::OR);
    std::shared_ptr<BinaryLogicFormula> aOrBShared2 = std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(),
                                                                                           LogicOperation::OR);
    Formula *notAOrB = new UnaryLogicFormula(aOrB->clone());
    std::shared_ptr<UnaryLogicFormula> notAorBShared = std::make_shared<UnaryLogicFormula>(aOrB->clone());
    Formula *notAOrB2 = new UnaryLogicFormula(aOrB->clone());

    deduction.addAssumption(a);
    deduction.addAssumptionWithMarker(notAOrB, 'a');

    std::shared_ptr<Rule> rule = RuleFactory::createRule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrBShared, a2});
    deduction.print();


    rule->apply(deduction);
    deduction.print();

    std::shared_ptr<BinaryLogicFormula> notAorBSharedAndAorB = std::make_shared<BinaryLogicFormula>(notAOrB->clone(),
                                                                                                    aOrB->clone(),
                                                                                                    LogicOperation::AND);
    std::shared_ptr<Rule> rule2 = RuleFactory::createRule(LogicOperation::AND, RuleResult::INTRODUCTION, {notAorBSharedAndAorB});


    rule2->apply(deduction);
    deduction.print();

    std::shared_ptr<Rule> rule3 = RuleFactory::createRule(LogicOperation::NOT, RuleResult::ELIMINATION,
               {std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR)});

    rule3->apply(deduction);
    deduction.print();

    std::shared_ptr<Rule> rule4 = RuleFactory::createRule(LogicOperation::NOT, RuleResult::INTRODUCTION, {std::make_shared<Variable>(a->getVariable())});

    rule4->apply(deduction);
    deduction.print();
    deduction.addAssumption(b);
    deduction.addAssumptionWithMarker(notAOrB, 'a');

    std::shared_ptr<Rule> rule5 = RuleFactory::createRule(LogicOperation::OR, RuleResult::INTRODUCTION, {aOrBShared, b2});

    rule5->apply(deduction);
    deduction.print();

    std::shared_ptr<BinaryLogicFormula> notAorBSharedAndAorB2 = std::make_shared<BinaryLogicFormula>(notAOrB->clone(),
                                                                                                     aOrB->clone(),
                                                                                                     LogicOperation::AND);
    std::shared_ptr<Rule> rule6 = RuleFactory::createRule(LogicOperation::AND, RuleResult::INTRODUCTION, {notAorBSharedAndAorB2});


    rule6->apply(deduction);
    deduction.print();

    std::shared_ptr<Rule> rule7 = RuleFactory::createRule(LogicOperation::NOT, RuleResult::ELIMINATION,
               {std::make_shared<BinaryLogicFormula>(a->clone(), b->clone(), LogicOperation::OR)});

    rule7->apply(deduction);
    deduction.print();

    std::shared_ptr<Rule> rule8 = RuleFactory::createRule(LogicOperation::NOT, RuleResult::INTRODUCTION, {std::make_shared<Variable>(b->getVariable())});

    rule8->apply(deduction);
    deduction.print();

    std::shared_ptr<BinaryLogicFormula> notAAndNotB = std::make_shared<BinaryLogicFormula>(
            new UnaryLogicFormula(a->clone()), new UnaryLogicFormula(b->clone()), LogicOperation::AND);

    std::shared_ptr<Rule> rule9 = RuleFactory::createRule(LogicOperation::AND, RuleResult::INTRODUCTION, {notAAndNotB});


    rule9->apply(deduction);
    deduction.print();

    std::shared_ptr<BinaryLogicFormula> notAAndNotB2 = std::make_shared<BinaryLogicFormula>(
            new UnaryLogicFormula(a->clone()), new UnaryLogicFormula(b->clone()), LogicOperation::AND);
    std::shared_ptr<UnaryLogicFormula> notAOrB3 = std::make_shared<UnaryLogicFormula>(aOrB->clone());

    std::shared_ptr<Rule> rule10 = RuleFactory::createRule(LogicOperation::IMPLIES, RuleResult::INTRODUCTION, {notAOrB3, notAAndNotB2}, {'a'});

    rule10->apply(deduction);
    deduction.print();
}

void testLogicFormulaFactory()
{
    std::string str;
    std::cin >> str;
    Formula* formula = FormulaFactory::createFormula(str);
    formula->print();
    delete formula;
}

void runAllTests()
{

    std::cout << "Test 1" << std::endl;
    test1();
    std::cout << "Test 2" << std::endl;
    test2();
    std::cout << "Test 3" << std::endl;
    test3();
    std::cout << "Test 4" << std::endl;
    test4();
    std::cout << "Test 5" << std::endl;
    test5();
    std::cout << "Test 6" << std::endl;
    test6();
    std::cout << "Test 7" << std::endl;
    test7();
    std::cout << "Test 8" << std::endl;
    test8();
    std::cout << "Test 9" << std::endl;
    test9();
    std::cout << "Test 10" << std::endl;
    test10();

    std::cout << "Proving De Morgan's Law" << std::endl;
    provingDeMorgan();
}

void runDeduction()
{
    DeductionController deductionController;
    deductionController.start();
}

int main()
{
    runDeduction();
    return 0;
}