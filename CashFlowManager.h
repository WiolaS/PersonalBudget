#ifndef CASHFLOWMANAGER_H
#define CASHFLOWMANAGER_H
#include <iostream>
#include <vector>
#include "CashFlow.h"
#include "IncomeFile.h"
#include "ExpenseFile.h"
#include "DateManager.h"
#include <windows.h>
#include <sstream>
#include <string>

using namespace std;

class CashFlowManager {

    const int LOGGED_IN_USER_ID;
    //vector <Date> dates;
    vector <CashFlow> incomes;
    vector <CashFlow> expenses;
    IncomeFile incomeFile;
    ExpenseFile expenseFile;
    DateManager dateManager;


public:
    CashFlowManager (string incomeFileName, string expenseFileName, int logedInUserId) : incomeFile (incomeFileName), expenseFile (expenseFileName), LOGGED_IN_USER_ID (logedInUserId) {

        incomes = incomeFile.loadIncomesOfTheLoggedinUserFromTheFile(LOGGED_IN_USER_ID);
        expenses = expenseFile.loadExpensesOfTheLoggedinUserFromTheFile(LOGGED_IN_USER_ID);
    };

    CashFlow addCashFlow (string typeOfCashFlow);
    int addIncome ();
    int addExpense ();
    void setACashFlowDate ();

    Date splitTheDateFromTheStringIntoIndividualElements (string dateEnteredByTheUser);
    string setTheDateOfTheCashFlow (string typeOfCashFlow);
    Date getDateFromTheSystem ();
    string enterTheNewDate (Date currentDate);

    string enterTheItemOfCashFlow ();
    float enterTheAmountOfCashFlow ();

    void sortIncomesByDate();
    void sortExpensesByDate();
    void showTheTotalAmountOfCashFlows (float sumOfIncomes, float sumOfExpenses);

    float calculateTheSumOfIncomesForTheCurrentMonth();
    float calculateTheSumOfExpensesForTheCurrentMonth();
    void showTheBalanceSheetOfTheCurrentMonth();

    float calculateTheSumOfIncomesForThePreviousMonth();
    float calculateTheSumOfExpensesForThePreviousMonth();
    void showTheBalanceSheetOfThePrevoiusMonth();

    float calculateTheSumOfIncomesForTheSelectedPeriod(Date startDate, Date endDate);
    float calculateTheSumOfExpensesForTheSelectedPeriod(Date startDate, Date endDate);
    void showTheBalanceSheetOfTheSelectedPeriod();


};

#endif // CASHFLOWMANAGER




