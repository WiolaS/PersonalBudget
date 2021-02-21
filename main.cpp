#include <iostream>
#include "PersonalBudget.h"
#include "UserManager.h"
#include <windows.h>

using namespace std;

int main() {
    PersonalBudget personalBudget ("UserFile.xml");

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "    >>> Welcome to the Personal Budget application! <<<"    << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    Sleep(3000);

    char choice;

    while (true) {
        if (!(personalBudget.checkThatUserIsLoggedIn())) {
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
                cout << endl << "There is no such option on the menu." << endl << endl;
                system("pause");
                break;
            }
        } else if (personalBudget.checkThatUserIsLoggedIn()) {
            choice = AuxiliaryMethods::selectAnOptionFromTheUserMenu();

            switch (choice) {
            case '1':
                personalBudget.addIncome();
                break;
            case '2':

                break;
            case '3':

                break;
            case '4':

                break;
            case '5':

                break;
            case '6':
                personalBudget.changePasswordOfLoggedInUser();
                break;
            case '7':
                //wylogujUzytkownika();
                break;
            }
        }
    }

    cout << "Show ID loogedin user: " << personalBudget.getIdLoggedUser() << endl;

    return 0;
}
