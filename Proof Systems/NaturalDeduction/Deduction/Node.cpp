#include "Node.h"

Node::Node(Formula *f) : formula(f), next(nullptr), previous()
{
}

Node::Node(Formula *f, char marker): formula(f), next(nullptr), previous(), marker(marker)
{
}

Formula *Node::getFormula() const
{
    return formula.get();
}

Node *Node::getNext() const
{
    return next.get();
}

void Node::setNext(Node *n)
{
    next.reset(n);
}

void Node::cross()
{
    crossed = true;
}

bool Node::isCrossed() const
{
    return crossed;
}

void Node::setNext(std::shared_ptr<Node> n)
{
    next = n;
}

std::shared_ptr<Node> Node::getNextShared() const
{
    return next;
}

void Node::addPrevious(Node *n)
{
    previous.push_back(std::shared_ptr<Node>(n));
}

void Node::addPrevious(std::shared_ptr<Node> n)
{
    previous.push_back(n);
}

std::vector<std::shared_ptr<Node>> &Node::getPrevious()
{
    return previous;
}

std::set<char> Node::getFreeVariables() const
{
    std::set<char> freeVariables = formula->getFreeVariables();
    for (const auto &prev: previous)
    {
        std::set<char> prevFreeVariables = prev->getFreeVariables();
        freeVariables.insert(prevFreeVariables.begin(), prevFreeVariables.end());
    }
    return freeVariables;
}

char Node::getMarker() const
{
    return marker;
}

void Node::setMarker(char marker)
{
    Node::marker = marker;
}

bool Node::hasMarker() const
{
    return marker;
}
