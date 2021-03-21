#include "DateManager.h"
#include "AuxiliaryMethods.h"
#include <iomanip>      // setprecision

using namespace std;


Date DateManager::getDateFromTheSystem() {
    Date date;
    SYSTEMTIME st;
    GetSystemTime(&st);

    date.setYear(st.wYear);
    date.setMonth(st.wMonth);
    date.setDay(st.wDay);

    return date;
}

string DateManager::combineDateElementsIntoAString(int year, int month, int day) {
    string stdate = "";
    string stYear = AuxiliaryMethods::convertIntToString (year);
    string stMonth = AuxiliaryMethods::convertIntToString (month);
    string stDay = AuxiliaryMethods::convertIntToString (day);

    if (month < 10) {
        stMonth = "0" + AuxiliaryMethods::convertIntToString (month);
    }
    if (day < 10) {
        stDay = "0" + AuxiliaryMethods::convertIntToString (day);
    }

    stdate = stYear + "-" + stMonth + "-" + stDay;

    return stdate;
}

string DateManager::replaceDateElementsWithASingleString (Date date) {
    string stDate = combineDateElementsIntoAString(date.getYear(), date.getMonth(), date.getDay());
    return stDate;
}

Date DateManager::splitTheDateFromTheStringIntoIndividualElements (string dateEnteredByTheUser) {
    Date date;
    string dateElement = "";
    int singleDateNumber = 1;

    for (int datePosition = 0; datePosition < dateEnteredByTheUser.length(); datePosition++) {
        if (dateEnteredByTheUser[datePosition] != '-') {
            dateElement += dateEnteredByTheUser[datePosition];
        } else {
            switch(singleDateNumber) {
            case 1:
                date.setYear(atoi(dateElement.c_str()));
                break;
            case 2:
                date.setMonth(atoi(dateElement.c_str()));
                break;
            case 3:
                date.setDay(atoi(dateElement.c_str()));
                break;
            }
            dateElement = "";
            singleDateNumber++;
        }
    }

    return date;
}

string DateManager::setTheDateOfTheCashFlow (string typeOfCashFlow) {

    string dateEnteredByTheUser;
    Date currentDateInNumberFormat;
    string dateOfTheCashFlow;
    char choice;

    currentDateInNumberFormat = getDateFromTheSystem ();
    choice = AuxiliaryMethods::selectAnOptionFromTheCashFlowMenu(typeOfCashFlow);

    switch (choice) {
    case '1':
        dateOfTheCashFlow = replaceDateElementsWithASingleString (currentDateInNumberFormat);
        system("pause");
        break;
    case '2':

        dateEnteredByTheUser = enterTheNewDate(currentDateInNumberFormat);
        dateOfTheCashFlow = dateEnteredByTheUser;

        system("pause");
        break;
    default:
        cout << endl << "There is no such option on the menu." << endl << endl;
        system("pause");
        break;

    }
    return dateOfTheCashFlow;
}


string DateManager::enterTheNewDate (Date currentDate) {
    string dateEnteredByTheUser;
    Date dateEnteredByTheUserInNumberFormat;

    cout << "Please enter date in the format yyyy-mm-dd: ";

    dateEnteredByTheUser = AuxiliaryMethods::loadLine();
    dateEnteredByTheUserInNumberFormat = splitTheDateFromTheStringIntoIndividualElements(dateEnteredByTheUser + "-");

    if (checkTheCorrectnesOfTheEnteredDate(dateEnteredByTheUserInNumberFormat, currentDate) == true)
        return dateEnteredByTheUser;
    else {
        cout << endl << "Please also note that the date should be in the range of" << endl;
        cout << "2000-01-01 to the last day of the current month: " << endl;
        dateEnteredByTheUser = enterTheNewDate (currentDate);
    }
}

bool DateManager::checkIfTheYearIsALeapYear (int year) {
    if (year % 4 == 0)
        return true;
    else
        return false;
}


int DateManager::checkHowManyDaysAMonthHas (int month, int year) {
    int numberOfDaysOfTheMonth = 0;

    if ((month % 2 != 0 && month < 8) || (month % 2 == 0 && month > 7)) {
        numberOfDaysOfTheMonth = 31;
    } else if (month == 2) {
        if (checkIfTheYearIsALeapYear(year)) {
            numberOfDaysOfTheMonth = 29;
        } else
            numberOfDaysOfTheMonth = 28;
    } else
        numberOfDaysOfTheMonth = 30;

    return numberOfDaysOfTheMonth;
}

bool DateManager::checkTheCorrectnesOfTheEnteredDate (Date dateEnteredByTheUser, Date currentDate) {

    if(checkIfTheYearNumberIsCorrect(dateEnteredByTheUser, currentDate) == true) {
        if(checkIfTheMonthNumberWithTheDayNumberAreCorrect(dateEnteredByTheUser, currentDate) == true)
            return true;
        else {
            return false;
        }
    } else
        return false;
}


bool DateManager::checkIfTheYearNumberIsCorrect (Date dateEnteredByTheUser, Date currentDate) {

    if(dateEnteredByTheUser.getYear() >= 2000 && dateEnteredByTheUser.getYear() <= currentDate.getYear()) {
        return true;
    } else
        return false;
}

bool DateManager::checkIfTheDayNumberIsCorrect (Date dateEnteredByTheUser, Date currentDate) {
    if (dateEnteredByTheUser.getDay() >= 1 && dateEnteredByTheUser.getDay() <= checkHowManyDaysAMonthHas (dateEnteredByTheUser.getMonth(), dateEnteredByTheUser.getYear()))
        return true;
    else
        return false;
}


bool DateManager::checkIfTheMonthNumberWithTheDayNumberAreCorrect (Date dateEnteredByTheUser, Date currentDate) {

    int numberOfTheFirstMonthOfTheYear = 1;
    int numberOfTheLastMonthOfTheYear = 12;

    if (dateEnteredByTheUser.getYear() == currentDate.getYear()) {
        if(dateEnteredByTheUser.getMonth() >= numberOfTheFirstMonthOfTheYear && dateEnteredByTheUser.getMonth() <= currentDate.getMonth()) {
            if (checkIfTheDayNumberIsCorrect(dateEnteredByTheUser, currentDate))
                return true;
            else
                return false;
        } else
            return false;
    } else {
        if  (dateEnteredByTheUser.getMonth() >= numberOfTheFirstMonthOfTheYear && dateEnteredByTheUser.getMonth() <= numberOfTheLastMonthOfTheYear) {
            if (checkIfTheDayNumberIsCorrect(dateEnteredByTheUser, currentDate))
                return true;
            else
                return false;
        } else
            return false;
    }
}


