#pragma once

#include <memory>
#include <vector>
#include "../Formulas/Formula.h"
#include "Node.h"

class Rule;

class Deduction {
private:
    std::vector<std::shared_ptr<Node>> assumptions;
    std::vector<std::shared_ptr<Node>> conclusions;

public:

    void print() const;

    void addAssumption(Formula *f);
    void addAssumptionWithMarker(Formula *f, char marker);

    void clear();

private:

    void printConclusions() const;

    static void getNodePointingToConclusion(const Formula *conclusion, Node *&node);

    static char getXNotInFormula(const Formula *formula);


    std::vector<std::shared_ptr<Node>>::iterator findAssumptionWithMarker(Formula *ruleAssumed, char marker);
    std::vector<std::shared_ptr<Node>>::iterator findAssumption(Formula *ruleAssumed);
    std::vector<std::shared_ptr<Node>>::iterator findConclusion(const Formula *pFormula);
    std::vector<std::shared_ptr<Node>>::iterator findConclusion(const Node *ruleAssumed);

    static bool findFormulaInVector(std::vector<Formula *> vector1, Formula *pFormula);

    friend class DisjunctionRule;
    friend class ImplicationRule;
    friend class ConjunctionRule;
    friend class NegationRule;
    friend class ExistentialRule;
    friend class UniversalRule;
    friend class FalseRule;

    void crossAssumptionsWithMarker(Formula *formula, char marker);
};
