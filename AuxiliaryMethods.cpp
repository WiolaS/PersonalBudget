#include "AuxiliaryMethods.h"
#include <windows.h>
#include <sstream> //convert
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip> //setprecision

using namespace std;

string AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces (float amount) {
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    string correctedStringAmount = ss.str();
    return correctedStringAmount;
}

string AuxiliaryMethods::loadLine() {
    string entry = "";
    getline(cin, entry);
    return entry;
}

char AuxiliaryMethods::loadCharacter() {
    string entry = "";
    char character  = {0};

    while (true) {
        getline(cin, entry);

        if (entry.length() == 1) {
            character = entry[0];
            break;
        }
        cout << "It is not a single character. Please enter the number again." << endl;
    }
    return character;
}

string AuxiliaryMethods::replaceCommaToDot (string amountOfCashFlowInStringFormat, char position) {
    amountOfCashFlowInStringFormat.replace(position,1,".");
    return amountOfCashFlowInStringFormat;
}

string AuxiliaryMethods::checkIfThereIsAComma(string amountOfCashFlowInStringFormat) {
    string signSought = ",";
    int position = 0;

    position = amountOfCashFlowInStringFormat.find(signSought);

    if (position != string::npos) {
        amountOfCashFlowInStringFormat = replaceCommaToDot(amountOfCashFlowInStringFormat, position);
    }
    return amountOfCashFlowInStringFormat;
}

string AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (float amountOfCasfFlow) {
    string amountInStringFormat = "";
    int lengthOfString = 0;

    amountInStringFormat = AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces(amountOfCasfFlow);
    lengthOfString = amountInStringFormat.length();
    lengthOfString = amountInStringFormat.length();

    while (lengthOfString < 12) {
        amountInStringFormat.insert(0," ");
        lengthOfString = amountInStringFormat.length();
    }
    return amountInStringFormat;
}

char AuxiliaryMethods::selectAnOptionFromTheMainMenu() {
    char choice;

    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "                      >>>    MAIN MENU    <<<                  " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1. REGISTRATION" << endl;
    cout << "2. LOGIN" << endl;
    cout << "3. EXIT" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Please enter the number of your choice: ";

    choice = loadCharacter();
    return choice;
}

char AuxiliaryMethods::selectAnOptionFromTheUserMenu () {
    char choice;

    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "                      >>>    USER MENU    <<<                  " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1. Add income" << endl;
    cout << "2. Add expense" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "3. Balance sheet from the current month" << endl;
    cout << "4. Balance sheet from the previous month" << endl;
    cout << "5. Balance sheet from the selected period" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "6. Change password" << endl;
    cout << "7. Logout" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Please enter the number of your choice: ";

    choice = loadCharacter();
    return choice;
}


char AuxiliaryMethods::selectAnOptionFromTheCashFlowMenu (string typeOfCashFlow) {
    char choice;
    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "                      >>> CASH FLOW MENU  <<<                  " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Is this "<< typeOfCashFlow << " from today?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Please enter the number of your choice: ";

    choice = loadCharacter();
    return choice;
}



void AuxiliaryMethods::layoutShowingTheSelectedCashFlow (string typeOfCashFlow) {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "                       >>>    " << typeOfCashFlow << "    <<<                  " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "|   Date    |   Amount    |Currency |             Item         " << endl;
}
