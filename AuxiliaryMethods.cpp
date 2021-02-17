#include "AuxiliaryMethods.h"
#include <windows.h>
#include <sstream> //konwersja int na str
#include <fstream>
#include <algorithm>
#include <string>
#include <iomanip> //serprecision

using namespace std;

static string convertIntToString(int number);
static int convertStringToInt(string number);

string AuxiliaryMethods::convertIntToString(int number) {
    ostringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

int AuxiliaryMethods::convertStringToInt(string number) {
    int numberInt;
    istringstream iss(number);
    iss >> numberInt;

    return numberInt;
}

string AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces (float amount) {

    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    string correctedStringAmount = ss.str();

    return correctedStringAmount;
}


float AuxiliaryMethods::convertStringToFloat(string number) {
    float numberFloat;
    istringstream iss(number);
    iss >> numberFloat;
    return numberFloat;

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

    /* for (int i  = 0; i < amountOfCashFlowInStringFormat.length(); i++) {
         if (amountOfCashFlowInStringFormat[i] == signSought) {
             amountOfCashFlowInStringFormat = replaceCommaToDot(amountOfCashFlowInStringFormat, i);
         }
     }*/
    return amountOfCashFlowInStringFormat;
}

char AuxiliaryMethods::selectAnOptionFromTheMainMenu() {
    char choice;

    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "          >>> THE MAIN MENU <<<" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1. REGISTRATION" << endl;
    cout << "2. LOGIN" << endl;
    cout << "3. EXIT" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Please enter the number of your choice: ";
    choice = loadCharacter();

    return choice;
}

char AuxiliaryMethods::selectAnOptionFromTheUserMenu () {
    char choice;

    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "          >>> THE USER MENU <<<" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1. Add revenue" << endl;
    cout << "2. Add expense" << endl;
    cout << "------------------------------------------" << endl;
    cout << "3. Balance sheet from the current month" << endl;
    cout << "4. Balance sheet from the previous month" << endl;
    cout << "5. Balance sheet from the selected period" << endl;
    cout << "------------------------------------------" << endl;
    cout << "6. Change password" << endl;
    cout << "7. Logout" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Please enter the number of your choice: ";

    choice = loadCharacter();

    return choice;
}


char AuxiliaryMethods::selectAnOptionFromTheCashFlowMenu () {

    char choice;
    system("cls");

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "          >>> THE CASH FLOW MENU <<<" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << endl << "Whether the cash flow is from today?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Please enter the number of your choice: ";

    choice = loadCharacter();

    return choice;
}
