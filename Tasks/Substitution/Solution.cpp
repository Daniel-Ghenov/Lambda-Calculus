#include <iostream>
#include "Terms/Abstraction.h"
#include "Terms/Variable.h"
#include "Terms/Application.h"

int main() {
    Variable variable ('c');
    Variable variable2 ('d');
    Variable variable3 ('p');
    Application application1 (variable, variable2);
    Abstraction abstraction (application1, 'c');

    Abstraction abstraction2 (variable3, 'p');

    abstraction.print();
    std::cout << std::endl;
    abstraction.substitute('d', abstraction2)->print();
}