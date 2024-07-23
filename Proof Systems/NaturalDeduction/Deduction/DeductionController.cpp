#include <iostream>
#include "DeductionController.h"
#include "../Formulas/FormulaFactory.h"
#include "Rules/RuleFactory.h"

void DeductionController::start()
{
    deduction.clear();

    while(true)
    {
        printControls();

        int choice;
        std::cin >> choice;

        switch(choice)
        {
            case 1:
            {
                handleAddAssumption();
                break;
            }
            case 2:
            {
                handleAddAssumptionWithMarker();
                break;
            }
            case 3:
            {
                deduction.print();
                break;
            }
            case 4:
            {
                handleApplyRule();
                break;
            }
            case 5:
            {
                deduction.clear();
                break;
            }
            case 6:
            {
                return;
            }
            default:
            {
                std::cout << "Invalid choice" << std::endl;
                break;
            }
        }
    }
}

void DeductionController::printControls()
{
    std::cout << "1. Add assumption"<<std::endl;
    std::cout << "2. Add assumption with marker"<<std::endl;
    std::cout << "3. Print"<<std::endl;
    std::cout << "4. Apply rule"<<std::endl;
    std::cout << "5. Clear"<<std::endl;
    std::cout << "6. Exit"<<std::endl;
}

void DeductionController::handleAddAssumption()
{
    std::cout << "Enter the assumption:" << std::endl;
    std::string formulaString;
    std::cin >> formulaString;
    auto formula = FormulaFactory::createFormula(formulaString);

    deduction.addAssumption(formula);
}

void DeductionController::handleAddAssumptionWithMarker()
{
    std::cout << "Enter the assumption:" << std::endl;
    std::string formulaString;
    std::cin >> formulaString;
    auto formula = FormulaFactory::createFormula(formulaString);

    std::cout << "Enter the marker:" << std::endl;
    char marker;
    std::cin >> marker;

    deduction.addAssumptionWithMarker(formula, marker);

}

void DeductionController::handleApplyRule()
{
    try {
        auto rule = RuleFactory::createRule();
        rule->apply(deduction);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << std::endl;
    }
}

