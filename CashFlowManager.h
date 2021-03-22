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
    vector <CashFlow> incomes;
    vector <CashFlow> expenses;
    IncomeFile incomeFile;
    ExpenseFile expenseFile;
    DateManager dateManager;

    CashFlow addCashFlow (string typeOfCashFlow);
    void setACashFlowDate ();
    Date splitTheDateFromTheStringIntoIndividualElements (string dateEnteredByTheUser);
    string setTheDateOfTheCashFlow (string typeOfCashFlow);
    Date getDateFromTheSystem ();
    string enterTheNewDate (Date currentDate);
    string enterTheItemOfCashFlow ();
    float enterTheAmountOfCashFlow ();
    void sortIncomesByDate();
    void sortExpensesByDate();
    bool checkIfThisCashFlowBelongsToTheLoggedInUser (int userID);
    float calculateTheSumOfIncomesForTheCurrentMonth();
    float calculateTheSumOfExpensesForTheCurrentMonth();
    float calculateTheSumOfIncomesForThePreviousMonth();
    float calculateTheSumOfExpensesForThePreviousMonth();
    float calculateTheSumOfIncomesForTheSelectedPeriod(Date startDate, Date endDate);
    float calculateTheSumOfExpensesForTheSelectedPeriod(Date startDate, Date endDate);


public:
    CashFlowManager (string incomeFileName, string expenseFileName, int logedInUserId) : incomeFile (incomeFileName), expenseFile (expenseFileName), LOGGED_IN_USER_ID (logedInUserId) {

        incomes = incomeFile.loadIncomesOfTheLoggedinUserFromTheFile(LOGGED_IN_USER_ID);
        expenses = expenseFile.loadExpensesOfTheLoggedinUserFromTheFile(LOGGED_IN_USER_ID);
    };

    int addIncome ();
    int addExpense ();
    void showTheTotalAmountOfCashFlows (float sumOfIncomes, float sumOfExpenses);
    void showTheBalanceSheetOfTheCurrentMonth();
    void showTheBalanceSheetOfThePrevoiusMonth();
    void showTheBalanceSheetOfTheSelectedPeriod();
};

#endif // CASHFLOWMANAGER




