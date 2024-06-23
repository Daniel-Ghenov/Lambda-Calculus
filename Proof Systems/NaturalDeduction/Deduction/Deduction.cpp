#include <stdexcept>
#include <iostream>
#include "Deduction.h"
#include "../Formulas/BinaryLogicFormula.h"

void Deduction::applyRule(Rule rule)
{
    switch (rule.getType())
    {

        case LogicOperation::AND:
            switch (rule.getResult()) {
                case RuleResult::INTRODUCTION:
                    applyConjunctionIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyConjunctionElimination(rule);
                    break;
            }
            break;
        case LogicOperation::OR:
            switch (rule.getResult()) {
                case RuleResult::INTRODUCTION:
                    applyDisjunctionIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyDisjunctionElimination(rule);
                    break;
            }
            break;
        case LogicOperation::IMPLIES:
            switch (rule.getResult()) {
                case RuleResult::INTRODUCTION:
                    applyImplicationIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyImplicationElimination(rule);
                    break;
            }
            break;
        case LogicOperation::NOT:
            switch (rule.getResult()) {
                case RuleResult::INTRODUCTION:
                    applyNegationIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyNegationElimination(rule);
                    break;
            }
            break;
        case LogicOperation::FOR_ALL:
            switch (rule.getResult()) {
                case RuleResult::INTRODUCTION:
                    applyUniversalIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyUniversalElimination(rule);
                    break;
            }
            break;
        case LogicOperation::EXISTS:
            switch (rule.getResult()) {
                case RuleResult::INTRODUCTION:
                    applyExistentialIntroduction(rule);
                    break;
                case RuleResult::ELIMINATION:
                    applyExistentialElimination(rule);
                    break;
            }
            break;
        default:
            throw std::invalid_argument("Invalid LogicOperation");
    }

}



void Deduction::addAssumption(Formula *f) {
    auto shared = std::make_shared<Node>(f);
    assumptions.push_back(shared);
    conclusions.push_back(shared);
}

void Deduction::applyImplicationIntroduction(Rule rule) {

    const auto ruleAssumed = rule.getPremises()[0].get();
    const auto conclusion = rule.getPremises()[1].get();

    auto i = findAssumption(ruleAssumed);

    if (i == assumptions.end()) {
        throw std::invalid_argument("Invalid assumption");
    }

    Node* node = (*i).get();
    while (node->getNext() != nullptr) {
        if (*(node->getNext()->getFormula()) == *conclusion) {
            break;
        }
        node = node->getNext();
    }

    if (node->getNext() == nullptr ||
        node->getNext()->getNext() != nullptr) {
        throw std::invalid_argument("Invalid conclusion");
    }

    node = node->getNext();
    Formula* f = new BinaryLogicFormula(ruleAssumed->clone(), conclusion->clone(), LogicOperation::IMPLIES);
    node->setNext(new Node(f));
    (*i)->cross();

    for (auto i = conclusions.begin(); i != conclusions.end(); i++) {
        if (i->get() == node) {
            conclusions.erase(i);
            break;
        }
    }
    conclusions.push_back(node->getNextShared());
}


void Deduction::applyDisjunctionIntroduction(Rule rule) {

}

void Deduction::applyDisjunctionElimination(Rule rule) {

}

void Deduction::applyConjunctionIntroduction(Rule rule) {

}

void Deduction::applyConjunctionElimination(Rule rule) {

    const auto expected = rule.getPremises()[0].get();
    const auto conclusion = rule.getPremises()[1].get();
    if (expected->getType() != FormulaType::BINARY_LOGIC) {
        throw std::invalid_argument("Invalid conjunction");
    }

    const auto conjunction = dynamic_cast<BinaryLogicFormula*>(expected);

    if ((conjunction)->getOperation() != LogicOperation::AND) {
        throw std::invalid_argument("Invalid conjunction");
    }

    auto i = findConclusion(expected);

    if (i == conclusions.end()) {
        throw std::invalid_argument("Invalid conjunction, must be in conclusions");
    }

    const auto left = conjunction->getLeftOperand();
    const auto right = conjunction->getRightOperand();

    if (!(*left == *conclusion) &&
        !(*right == *conclusion))
    {
        throw std::invalid_argument("Invalid conclusion to eliminate");
    }


    std::shared_ptr<Node> node;
    if (*left == *conclusion) {
        node = std::make_shared<Node>(left->clone());
    } else {
        node = std::make_shared<Node>(right->clone());
    }

    i->get()->setNext(node);
    conclusions.erase(i);
    conclusions.push_back(node);

}

void Deduction::applyImplicationElimination(Rule rule) {

}

void Deduction::applyNegationIntroduction(Rule rule) {

}

void Deduction::applyNegationElimination(Rule rule) {

}

void Deduction::applyExistentialIntroduction(Rule rule) {

}

void Deduction::applyExistentialElimination(Rule rule) {

}

void Deduction::applyUniversalIntroduction(Rule rule) {

}

void Deduction::applyUniversalElimination(Rule rule) {

}


std::vector<std::shared_ptr<Node>>::iterator Deduction::findAssumption(Formula* ruleAssumed) {

    for(auto assumption = assumptions.begin(); assumption != assumptions.end(); assumption++) {
        if (*((assumption)->get()->getFormula()) == *(ruleAssumed)) {
            return assumption;
        }
    }

    return assumptions.end();
}

void Deduction::print() {

    std::cout<<"Assumptions: [";
    bool first = true;
    for (const auto& assumption : assumptions) {
        if (!first) {
            std::cout<<", ";
        } else {
            first = false;
        }
        if (!assumption->isCrossed()){
            assumption->getFormula()->print();
        }
    }
    std::cout<<"]"<<std::endl;

    printConclusions();

}

void Deduction::printConclusions() {
    std::cout<<"Conclusions: [";
    bool first = true;
    for (const auto& conclusion : conclusions) {
        if (findAssumption(conclusion->getFormula()) == assumptions.end())
        {
            if (!first) {
                std::cout<<", ";
            } else {
                first = false;
            }
            conclusion->getFormula()->print();
        }
    }
    std::cout<<"]"<<std::endl;
}

std::vector<std::shared_ptr<Node>>::iterator Deduction::findConclusion(Formula *const ruleAssumed) {
    for(auto conclusion = conclusions.begin(); conclusion != conclusions.end(); conclusion++) {
        if (*((conclusion)->get()->getFormula()) == *(ruleAssumed)) {
            return conclusion;
        }
    }

    return conclusions.end();
}
