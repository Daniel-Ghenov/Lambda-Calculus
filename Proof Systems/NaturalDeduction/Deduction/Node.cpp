#include "Node.h"

Formula *Node::getFormula() const {
    return formula.get();
}

Node *Node::getNext() const {
    return next.get();
}

void Node::setNext(Node *n) {
    next.reset(n);
}

void Node::cross() {
    crossed = true;
}

bool Node::isCrossed() const {
    return crossed;
}

void Node::setNext(std::shared_ptr<Node> n) {
    next = n;
}

std::shared_ptr<Node> Node::getNextShared() const {
    return next;
}
