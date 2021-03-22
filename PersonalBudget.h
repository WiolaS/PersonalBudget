#ifndef PERSONALBUDGET_H
#define PERSONALBUDGET_H
#include <iostream>
#include "UserManager.h"
#include "CashFlowManager.h"
#include "TextFile.h"

using namespace std;

class PersonalBudget {

    UserManager userManager;
    CashFlowManager *cashFlowManager;
    IncomeFile incomeFile;
    ExpenseFile expenseFile;

public:
    PersonalBudget(string userFileName, string incomeFileName, string expenseFileName): userManager(userFileName), incomeFile (incomeFileName), expenseFile (expenseFileName){
        cashFlowManager = NULL;
    };

    ~PersonalBudget() {
        delete cashFlowManager;
        cashFlowManager = NULL;
    }

    void registerUser();
    void login();
    vector <User> loadUsersFromFile();
    void changePasswordOfLoggedInUser();
    int getIdOfLoggedInUser();
    bool checkIfUserIsLoggedIn();
    void logout();
    void addIncome();
    void addExpense();
    void showTheBalanceSheetOfTheCurrentMonth();
    void showTheBalanceSheetOfThePrevoiusMonth();
    void showTheBalanceSheetOfTheSelectedPeriod();

};

#endif // KSIAZKAADRSOWA

