#pragma once

#include "Deduction.h"

class DeductionController
{
private:
    Deduction deduction;
public:
    DeductionController() = default;

    void start();

private:
    static void printControls() ;

    void handleAddAssumption();

    void handleAddAssumptionWithMarker();

    void handleApplyRule();
};
