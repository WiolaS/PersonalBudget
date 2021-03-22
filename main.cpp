#include <iostream>
#include "PersonalBudget.h"
#include "UserManager.h"

using namespace std;

int main() {
    PersonalBudget personalBudget ("users.xml", "incomes.xml", "expenses.xml");

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "         >>> Welcome to the Personal Budget application! <<<"    << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    Sleep(2500);

    char choice;
    while (true) {
        if (!(personalBudget.checkIfUserIsLoggedIn())) {
            choice = AuxiliaryMethods::selectAnOptionFromTheMainMenu();

            switch (choice) {
            case '1':
                personalBudget.registerUser();
                system("pause");
                break;
            case '2':
                personalBudget.login();
                system("pause");
                break;
            case '3':
                exit(0);
                break;
            default:
                cout << endl << "There is no such option. Please try again." << endl << endl;
                system("pause");
                break;
            }
        } else if (personalBudget.checkIfUserIsLoggedIn()) {
            choice = AuxiliaryMethods::selectAnOptionFromTheUserMenu();

            switch (choice) {
            case '1':
                personalBudget.addIncome();
                break;
            case '2':
                personalBudget.addExpense();
                break;
            case '3':
                personalBudget.showTheBalanceSheetOfTheCurrentMonth();
                system("pause");
                break;
            case '4':
                personalBudget.showTheBalanceSheetOfThePrevoiusMonth();
                system("pause");
                break;
            case '5':
                personalBudget.showTheBalanceSheetOfTheSelectedPeriod();
                system("pause");
                break;
            case '6':
                personalBudget.changePasswordOfLoggedInUser();
                system("pause");
                break;
            case '7':
                personalBudget.logout();
                break;
            }
        }
    }
    return 0;
}
