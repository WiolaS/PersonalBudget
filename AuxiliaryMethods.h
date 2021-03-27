#ifndef AUXILIARYMETHODS_H
#define AUXILIARYMETHODS_H
#include <iostream>
#include "User.h"

using namespace std;

class AuxiliaryMethods {

public:
    static string convertFloatToStringAndSetPrecisionToTwoDecimalPlaces (float amount);
    static string loadLine();
    static string replaceCommaWithDot();
    static char selectAnOptionFromTheMainMenu();
    static char selectAnOptionFromTheUserMenu();
    static char selectAnOptionFromTheCashFlowMenu(string typeOfCashFlow);
    static char loadCharacter();
    static string replaceCommaToDot (string amountOfCashFlowInStringFormat, char position);
    static string checkIfThereIsAComma(string amountOfCashFlowInStringFormat);
    static void layoutShowingTheSelectedCashFlow (string typeOfCashFlow);
    static string changeTheFloatTypeToStringOfLength12 (float amountOfCasfFlow);

};

#endif // AUXILIARYMETHODS





