#ifndef CASHFLOWMANAGER_H
#define CASHFLOWMANAGER_H
#include <iostream>
#include <vector>
#include "CashFlow.h"
//#include "Date.h"  // it is included in CashFlow.h
#include "IncomeFile.h"
#include "ExpenseFile.h"
#include <windows.h>
#include <sstream>
#include <string>

using namespace std;

class CashFlowManager {

    const int LOGGED_IN_USER_ID;
    vector <Date> dates;
    vector <CashFlow> incomes;
    vector <CashFlow> expenses;
    IncomeFile incomeFile;
    ExpenseFile expenseFile;


public:
    CashFlowManager (string incomeFileName, string expenseFileName, int logedInUserId) : incomeFile (incomeFileName), expenseFile (expenseFileName), LOGGED_IN_USER_ID (logedInUserId) {

        incomes = incomeFile.loadIncomesOfTheLoggedinUserFromTheFile(LOGGED_IN_USER_ID);
        expenses = expenseFile.loadExpensesOfTheLoggedinUserFromTheFile(LOGGED_IN_USER_ID);
    };

    CashFlow addCashFlow (string typeOfCashFlow);
    int addIncome ();
    int addExpense ();
    void setACashFlowDate ();

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
    string enterTheItemOfCashFlow ();
    float enterTheAmountOfCashFlow ();

    double calculateTheSumOfIncomesForTheCurrentMonth();
    double calculateTheSumOfExpensesForTheCurrentMonth();
    void showTheBalanceSheetOfTheCurrentMonth();

    double calculateTheSumOfIncomesForThePreviousMonth();
    double calculateTheSumOfExpensesForThePreviousMonth();
    void showTheBalanceSheetOfThePrevoiusMonth();

    float calculateTheSumOfIncomesForTheSelectedPeriod();
    float calculateTheSumOfExpensesForTheSelectedPeriod(Date startDate, Date endDate);
    void showTheBalanceSheetOfTheSelectedPeriod();

    //void selectIncomesFromThePreviousMonth ();


};

#endif // CASHFLOWMANAGER


