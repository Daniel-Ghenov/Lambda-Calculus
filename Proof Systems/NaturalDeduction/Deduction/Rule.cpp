#include <stdexcept>
#include "Rule.h"

int Rule::getRuleArgumentCount() const {
    switch (this->result) {
        case RuleResult::INTRODUCTION:
            return getRuleArgumentCountIntroduction();
        case RuleResult::ELIMINATION:
            return getRuleArgumentCountElimination();
        default:
            throw std::invalid_argument("Invalid RuleResult");
    }
}

int Rule::getRuleArgumentCountIntroduction() const {
    switch (this->type) {
        case LogicOperation::AND:
        case LogicOperation::OR:
        case LogicOperation::IMPLIES:
        case LogicOperation::EXISTS:
            return 2;
        case LogicOperation::NOT:
        case LogicOperation::FOR_ALL:
            return 1;

        default:
            throw std::invalid_argument("Invalid LogicOperation");
    }
}

int Rule::getRuleArgumentCountElimination() const {
    switch (this->type) {
        case LogicOperation::AND:
        case LogicOperation::OR:
        case LogicOperation::IMPLIES:
        case LogicOperation::FOR_ALL:
        case LogicOperation::EXISTS:
            return 2;
        case LogicOperation::NOT:
            return 1;
        default:
            throw std::invalid_argument("Invalid LogicOperation");
    }
}

Rule::Rule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>>&& premises): type(type), result(result), premises(std::move(premises)){
    if (this->premises.size() != getRuleArgumentCount()) {
        throw std::invalid_argument("Invalid number of premises");
    }
}

LogicOperation Rule::getType() const {
    return type;
}

RuleResult Rule::getResult() const {
    return result;
}

std::vector<std::shared_ptr<Formula>> Rule::getPremises() const {
    return premises;
}
