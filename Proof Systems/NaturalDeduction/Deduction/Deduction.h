#pragma once

#include <memory>
#include <vector>
#include "../Formulas/Formula.h"
#include "Node.h"
#include "Rule.h"

class Deduction
{
private:
    std::vector<std::shared_ptr<Node>> assumptions;
    std::vector<std::shared_ptr<Node>> conclusions;

public:

    void applyRule(Rule rule);
    void print();
    void addAssumption(Formula *f);

private:
    void applyDisjunctionIntroduction(Rule rule);
    void applyDisjunctionElimination(Rule rule);
    void applyConjunctionIntroduction(Rule rule);
    void applyConjunctionElimination(Rule rule);
    void applyImplicationIntroduction(Rule rule);
    void applyImplicationElimination(Rule rule);
    void applyNegationIntroduction(Rule rule);
    void applyNegationElimination(Rule rule);
    void applyExistentialIntroduction(Rule rule);
    void applyExistentialElimination(Rule rule);
    void applyUniversalIntroduction(Rule rule);
    void applyUniversalElimination(Rule rule);

    std::vector<std::shared_ptr<Node>>::iterator findAssumption(Formula *ruleAssumed);

    void printConclusions();

    std::vector<std::shared_ptr<Node>>::iterator findConclusion(Formula *const pFormula);
};
