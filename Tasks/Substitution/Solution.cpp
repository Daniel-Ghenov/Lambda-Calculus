#include <iostream>
#include "Terms/Abstraction.h"
#include "Terms/Variable.h"
#include "Terms/Application.h"

int main() {
    Variable variable ('c');
    Abstraction abstraction (variable, 'c');
    Application application (variable, abstraction);


}