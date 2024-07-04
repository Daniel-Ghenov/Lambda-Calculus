#include <iostream>
#include "SubstitutionFormula.h"

SubstitutionFormula::SubstitutionFormula(Formula *main, Formula *from, Formula *to) : main(main), from(from), to(to),
                                                                                      Formula(FormulaType::SUBSTITUTION)
{}

Formula *SubstitutionFormula::getMain() const
{
    return main.get();
}

Formula *SubstitutionFormula::getFrom() const
{
    return from.get();
}

Formula *SubstitutionFormula::getTo() const
{
    return to.get();
}

void SubstitutionFormula::print() const
{
    std::cout << "(";
    main->print();
    std::cout << "[";
    from->print();
    std::cout << "->";
    to->print();
    std::cout << "])";
}

bool SubstitutionFormula::operator==(const Formula &other) const
{

    auto &otherSubstitution = dynamic_cast<const SubstitutionFormula &>(other);
    return *main == *otherSubstitution.main && *from == *otherSubstitution.from && *to == *otherSubstitution.to;
}

std::set<char> SubstitutionFormula::getFreeVariables() const
{
    std::set<char> result = main->getFreeVariables();
    for (char c: from->getFreeVariables())
    {
        result.insert(c);
    }
    for (char c: to->getFreeVariables())
    {
        result.insert(c);
    }
    return result;
}

Formula *SubstitutionFormula::clone() const
{
    return new SubstitutionFormula(main->clone(), from->clone(), to->clone());
}

