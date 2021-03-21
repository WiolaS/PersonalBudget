#ifndef DATEMANAGER_H
#define DATEMANAGER_H
#include <iostream>
#include <vector>
#include "Date.h"
#include <windows.h>
#include <sstream>
#include <string>

using namespace std;

class DateManager {

public:
    //DateManager {
    //};

    string replaceDateElementsWithASingleString (Date date);
    Date splitTheDateFromTheStringIntoIndividualElements (string dateEnteredByTheUser);
    string combineDateElementsIntoAString (int year, int month, int day);
    string setTheDateOfTheCashFlow (string typeOfCashFlow);
    Date getDateFromTheSystem ();
    string enterTheNewDate (Date currentDate);
    bool checkIfTheYearIsALeapYear (int year);
    int checkHowManyDaysAMonthHas (int month, int year);

    bool checkTheCorrectnesOfTheEnteredDate (Date dateEnteredByTheUser, Date currentDate) ;
    bool checkIfTheYearNumberIsCorrect (Date dateEnteredByTheUser, Date currentDate);
    bool checkIfTheDayNumberIsCorrect (Date dateEnteredByTheUser, Date currentDate);
    bool checkIfTheMonthNumberWithTheDayNumberAreCorrect (Date dateEnteredByTheUser, Date currentDate);
};

#endif // DATEMANAGER
