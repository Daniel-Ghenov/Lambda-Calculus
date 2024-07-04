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
}