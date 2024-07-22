#pragma once

#include "Rule.h"

class RuleFactory
{
private:
    RuleFactory() = default;
public:
    static std::shared_ptr<Rule> createRule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>>&& premises);

    static std::shared_ptr<Rule> createRule(LogicOperation type, RuleResult result, std::vector<std::shared_ptr<Formula>> &&premises,
               std::vector<char> &&markers);

    static std::shared_ptr<Rule> createRule(std::istream& in);
};
