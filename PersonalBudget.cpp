#include "PersonalBudget.h"
#include <windows.h> //system("cls")

using namespace std;


void PersonalBudget::registerUser()
{
    userManager.registerUser();
}

int PersonalBudget::login()
{
    userManager.login();
    if (userManager.checkThatUserIsLoggedIn()) {
        cashFlowManager = new CashFlowManager (incomeFile.getFileName(), expenseFile.getFileName(), userManager.getIdOfLoggedInUser());

    }
}

vector <User> PersonalBudget::loadUsersFromFile()
{
    userManager.loadUsersFromFile();
}

void PersonalBudget::changePasswordOfLoggedInUser()
{
    userManager.changePasswordOfLoggedInUser();
}


int PersonalBudget::getIdOfLoggedInUser()
{
    userManager.getIdOfLoggedInUser();

}

bool PersonalBudget::checkThatUserIsLoggedIn()
{
    return userManager.checkThatUserIsLoggedIn();

}

void PersonalBudget::addIncome()
{
    cashFlowManager -> addIncome();
}


void PersonalBudget::addExpense()
{
    cashFlowManager -> addExpense();
}

void PersonalBudget::showTheBalanceSheetOfTheCurrentMonth()
{
    return cashFlowManager -> showTheBalanceSheetOfTheCurrentMonth();
}

float PersonalBudget::showTheBalanceSheetOfThePrevoiusMonth()
{
    return cashFlowManager -> showTheBalanceSheetOfThePrevoiusMonth();
}

void PersonalBudget::showTheBalanceSheetOfTheSelectedPeriod()
{
    return cashFlowManager -> showTheBalanceSheetOfTheSelectedPeriod();
}


