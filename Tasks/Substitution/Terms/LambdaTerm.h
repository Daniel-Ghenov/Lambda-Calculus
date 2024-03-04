#pragma once
#include <set>

class LambdaTerm {
public:
    virtual ~LambdaTerm() = 0;
    virtual const std::set<char>& getFreeVariables() const = 0;
    virtual const std::set<char>& getBoundVariables() const = 0;
    virtual LambdaTerm* clone() const = 0 ;
};

