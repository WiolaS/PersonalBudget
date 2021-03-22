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

    string replaceDateElementsWithASingleString (Date date);
    string combineDateElementsIntoAString (int year, int month, int day);
    int checkHowManyDaysAMonthHas (int month, int year);
    bool checkIfTheYearIsALeapYear (int year);
    bool checkTheCorrectnesOfTheEnteredDate (Date dateEnteredByTheUser, Date currentDate) ;
    bool checkIfTheYearNumberIsCorrect (Date dateEnteredByTheUser, Date currentDate);
    bool checkIfTheDayNumberIsCorrect (Date dateEnteredByTheUser, Date currentDate);
    bool checkIfTheMonthNumberWithTheDayNumberAreCorrect (Date dateEnteredByTheUser, Date currentDate);

public:
    Date getDateFromTheSystem ();
    Date splitTheDateFromTheStringIntoIndividualElements (string dateEnteredByTheUser);
    string enterTheNewDate (Date currentDate);
    string setTheDateOfTheCashFlow (string typeOfCashFlow);

};

#endif // DATEMANAGER
