#pragma once

#include <memory>
#include <vector>
#include "../Formulas/Formula.h"
#include "../Formulas/UnaryLogicFormula.h"

class Node
{
private:
    std::unique_ptr<Formula> formula;
    std::shared_ptr<Node> next;
    std::vector<std::shared_ptr<Node>> previous;
    bool crossed = false;
public:
    explicit Node(Formula *f): formula(f), next(nullptr), previous(){ };
    ~Node() = default;
    [[nodiscard]] Formula *getFormula() const;
    [[nodiscard]] std::shared_ptr<Node> getNextShared() const;
    [[nodiscard]] Node *getNext() const;
    void setNext(Node *n);
    void setNext(std::shared_ptr<Node> n);
    void addPrevious(Node *n);
    void addPrevious(std::shared_ptr<Node> n);
    [[nodiscard]] std::vector<std::shared_ptr<Node>>& getPrevious();
    [[nodiscard]] std::set<char> getFreeVariables() const;
    void cross();
    [[nodiscard]] bool isCrossed() const;

};
