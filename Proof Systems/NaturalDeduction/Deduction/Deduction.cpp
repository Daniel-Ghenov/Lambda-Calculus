#include <stdexcept>
#include <iostream>
#include "Deduction.h"
#include "../Formulas/BinaryLogicFormula.h"
#include "../Formulas/UnaryLogicFormula.h"

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

void Deduction::applyDisjunctionIntroduction(Rule rule) {

    auto disjunction = rule.getPremises()[0].get();
    auto current = rule.getPremises()[1].get();

    if (disjunction->getType() != FormulaType::BINARY_LOGIC) {
        throw std::invalid_argument("Invalid disjunction");
    }

    auto binary = dynamic_cast<BinaryLogicFormula*>(disjunction);

    if (binary == nullptr || binary->getOperation() != LogicOperation::OR) {
        throw std::invalid_argument("Invalid disjunction");
    }

    auto left = binary->getLeftOperand();
    auto right = binary->getRightOperand();

    if (!(*left == *current) &&
        !(*right == *current))
    {
        throw std::invalid_argument("Invalid current");
    }

    auto leftIter = findConclusion(current);

    if (leftIter == conclusions.end()) {
        throw std::invalid_argument("Invalid current, must be in conclusions");
    }

    std::shared_ptr<Node> node = std::make_shared<Node>(disjunction->clone());
    leftIter->get()->setNext(node);

    conclusions.erase(findConclusion(current));
    conclusions.push_back(node);
}

void Deduction::applyDisjunctionElimination(Rule rule) {
    auto disjunction = rule.getPremises()[0].get();
    auto implied = rule.getPremises()[1].get();

    if (disjunction->getType() != FormulaType::BINARY_LOGIC) {
        throw std::invalid_argument("Invalid disjunction");
    }

    auto binary = dynamic_cast<BinaryLogicFormula*>(disjunction);
    if (binary == nullptr || binary->getOperation() != LogicOperation::OR) {
        throw std::invalid_argument("Invalid disjunction");
    }

    auto disConclusion = findConclusion(disjunction);

    if (disConclusion == conclusions.end()) {
        throw std::invalid_argument("Invalid disjunction, must be in conclusions");
    }

    auto left = binary->getLeftOperand();
    auto right = binary->getRightOperand();

    auto leftIter = findAssumption(left);
    if (leftIter == assumptions.end()) {
        throw std::invalid_argument("Invalid left operand");
    }

    auto rightIter = findAssumption(right);
    if (rightIter == assumptions.end()) {
        throw std::invalid_argument("Invalid right operand");
    }
    auto node = (*leftIter).get();
    getNodePointingToConclusion(implied, node);

    auto nodeRight = (*rightIter).get();
    getNodePointingToConclusion(implied, nodeRight);

    std::shared_ptr<Node> newNode = std::make_shared<Node>(implied->clone());
    node->setNext(newNode);
    nodeRight->setNext(newNode);
    disConclusion->get()->setNext(newNode);

    leftIter->get()->cross();
    rightIter->get()->cross();
    conclusions.push_back(newNode);

    conclusions.erase(findConclusion(disjunction));
    conclusions.erase(findConclusion(node));
    conclusions.erase(findConclusion(nodeRight));
}

void Deduction::applyConjunctionIntroduction(Rule rule) {
    const auto conjunction = rule.getPremises()[0].get();

    if (conjunction->getType() != FormulaType::BINARY_LOGIC) {
        throw std::invalid_argument("Invalid conjunction");
    }

    const auto binary = dynamic_cast<BinaryLogicFormula*>(conjunction);

    if (binary == nullptr || binary->getOperation() != LogicOperation::AND) {
        throw std::invalid_argument("Invalid conjunction");
    }

    const auto left = binary->getLeftOperand();
    const auto right = binary->getRightOperand();

    auto leftIter = findConclusion(left);

    if (leftIter == assumptions.end()) {
        throw std::invalid_argument("Invalid left operand");
    }

    auto rightIter = findConclusion(right);

    if (rightIter == assumptions.end()) {
        throw std::invalid_argument("Invalid right operand");
    }

    std::shared_ptr<Node> node = std::make_shared<Node>(binary->clone());

    leftIter->get()->setNext(node);
    rightIter->get()->setNext(node);

    conclusions.erase(findConclusion(left));
    conclusions.erase(findConclusion(right));
    conclusions.push_back(node);

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

void Deduction::applyImplicationIntroduction(Rule rule) {

    const auto ruleAssumed = rule.getPremises()[0].get();
    const auto conclusion = rule.getPremises()[1].get();

    auto i = findAssumption(ruleAssumed);

    if (i == assumptions.end()) {
        throw std::invalid_argument("Invalid assumption");
    }
    Node *node = (*i).get();
    getNodePointingToConclusion(conclusion, node);

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

void Deduction::applyImplicationElimination(Rule rule) {

    const auto implication = rule.getPremises()[0].get();

    if (implication->getType() != FormulaType::BINARY_LOGIC) {
        throw std::invalid_argument("Invalid implication");
    }

    const auto binary = dynamic_cast<BinaryLogicFormula*>(implication);

    if (binary->getOperation() != LogicOperation::IMPLIES) {
        throw std::invalid_argument("Invalid implication");
    }

    const Formula* implied = binary->getLeftOperand();

    auto implIter = findConclusion(implication);

    if (implIter == conclusions.end()) {
        throw std::invalid_argument("Invalid implication, must be in conclusions");
    }

    auto impliedIter = findConclusion(implied);

    if (impliedIter == conclusions.end()) {
        throw std::invalid_argument("Invalid implied, must be in conclusions");
    }

    std::shared_ptr<Node> node = std::make_shared<Node>(binary->getRightOperand()->clone());

    implIter->get()->setNext(node);
    conclusions.erase(findConclusion(implication));
    conclusions.push_back(node);
    impliedIter->get()->setNext(node);
    conclusions.erase(findConclusion(implied));

}

void Deduction::applyNegationIntroduction(Rule rule) {

    auto negation = rule.getPremises()[0].get();

    auto negationIter = findAssumption(negation);
    Node* node = negationIter->get();
    getNodePointingToConclusion(UnaryLogicFormula::getFalse(), node);

    std::shared_ptr<Node> conclusion;
    if (negation->getType() == FormulaType::UNARY_LOGIC) {

        auto unary = dynamic_cast<UnaryLogicFormula*>(negation);

        conclusion = std::make_shared<Node>(unary->getOperand());
    } else {
        conclusion = std::make_shared<Node>(new UnaryLogicFormula(negation->clone()));
    }

    node->setNext(conclusion);
    negationIter->get()->cross();
    conclusions.erase(findConclusion(negation));
    conclusions.push_back(conclusion);

}

void Deduction::applyNegationElimination(Rule rule) {

    auto premise = rule.getPremises()[0].get();
    Formula* notNegated;
    Formula* negated;

    if (premise->getType() == FormulaType::UNARY_LOGIC) {
        auto unary = dynamic_cast<UnaryLogicFormula*>(premise);
        if (unary->getOperation() != LogicOperation::NOT) {
            throw std::invalid_argument("Invalid negation");
        }
        notNegated = unary->getOperand();
        negated = unary;
    } else {
        notNegated = premise;
        negated = new UnaryLogicFormula(premise->clone());
    }

    Formula* contradiction = new BinaryLogicFormula(notNegated->clone(), negated->clone(), LogicOperation::AND);

    auto contradictionIter = findConclusion(contradiction);

    std::shared_ptr<Node> node = std::make_shared<Node>(UnaryLogicFormula::getFalse());

    contradictionIter->get()->setNext(node);
    conclusions.erase(findConclusion(contradiction));
    conclusions.push_back(node);


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
        if (!assumption->isCrossed()){
            if (!first) {
                std::cout<<", ";
            } else {
                first = false;
            }
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
    std::cout<<"]"<<std::endl<<std::endl;
}

std::vector<std::shared_ptr<Node>>::iterator Deduction::findConclusion(const Formula *const ruleAssumed) {
    for(auto conclusion = conclusions.begin(); conclusion != conclusions.end(); conclusion++) {
        if (*((conclusion)->get()->getFormula()) == *(ruleAssumed)) {
            return conclusion;
        }
    }

    return conclusions.end();
}

std::vector<std::shared_ptr<Node>>::iterator Deduction::findConclusion(const Node *const ruleAssumed) {
    for(auto conclusion = conclusions.begin(); conclusion != conclusions.end(); conclusion++) {
        if (conclusion->get() == ruleAssumed) {
            return conclusion;
        }
    }

    return conclusions.end();
}


void Deduction::getNodePointingToConclusion(const Formula *conclusion, Node *&node) {

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
}

char Deduction::getXNotInFormula(const Formula *formula) {
    std::set<char> free = formula->getFreeVariables();
    for (char c = 'a'; c <= 'z'; c++) {
        if (free.find(c) == free.end()) {
            return c;
        }
    }
    throw std::invalid_argument("No free variables");
}
