#include <stdexcept>
#include "LogicFormula.h"

std::string logicOperationToString(LogicOperation op)
{
    switch (op)
    {
        case LogicOperation::AND:
            return "&";
        case LogicOperation::OR:
            return "|";
        case LogicOperation::IMPLIES:
            return "->";
        case LogicOperation::NOT:
            return "!";
        case LogicOperation::BIDIRECTIONAL_IMPLIES:
            return "<->";
        case LogicOperation::FOR_EACH:
            return "\\/";
        case LogicOperation::EXISTS:
            return "E";
    }
    throw std::invalid_argument("Invalid operation");
}

LogicOperation logicOperationFromString(const std::string_view &str)
{
    if (str.find('&') == 0)
    {
        return LogicOperation::AND;
    }
    if (str.find('|') == 0)
    {
        return LogicOperation::OR;
    }
    if (str.find("->") == 0)
    {
        return LogicOperation::IMPLIES;
    }
    if (str.find('!') == 0)
    {
        return LogicOperation::NOT;
    }
    if (str.find("<->") == 0)
    {
        return LogicOperation::BIDIRECTIONAL_IMPLIES;
    }
    if (str.find("\\/") == 0)
    {
        return LogicOperation::FOR_EACH;
    }
    if (str.find('E') == 0)
    {
        return LogicOperation::EXISTS;
    }
    throw std::invalid_argument("Invalid operation");
}