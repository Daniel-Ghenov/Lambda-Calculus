#pragma once

#include <memory>
#include "../Formulas/Formula.h"
#include "../Formulas/UnaryLogicFormula.h"

class Node
{
private:
    std::unique_ptr<Formula> formula;
    std::shared_ptr<Node> next;
    bool crossed = false;
public:
    explicit Node(Formula *f): formula(f), next(nullptr){ };
    ~Node() = default;
    [[nodiscard]] Formula *getFormula() const;
    [[nodiscard]] std::shared_ptr<Node> getNextShared() const;
    [[nodiscard]] Node *getNext() const;
    void setNext(Node *n);
    void setNext(std::shared_ptr<Node> n);
    void cross();
    [[nodiscard]] bool isCrossed() const;

};
