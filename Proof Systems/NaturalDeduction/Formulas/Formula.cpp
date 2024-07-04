#include "Formula.h"

bool Formula::operator==(const Formula &other) const
{
    return this->getType() == other.getType();
}
