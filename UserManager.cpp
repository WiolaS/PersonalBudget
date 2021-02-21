#include "UserManager.h"
#include "AuxiliaryMethods.h"
#include <windows.h>

using namespace std;

bool UserManager::checkIfSuchLoginAlreadyExists(string login) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getLogin() == login) {
            cout << endl << "There is a user with this login." << endl;
            return true;
        }
    }
    return false;
}

User UserManager::enterNewUserData() {
    User user;
    user.setUserId(getIdOfNewUser());
    string login;
    do {
        cout << "Please enter login: ";
        login = AuxiliaryMethods::loadLine();
        user.setLogin(login);
    } while (checkIfSuchLoginAlreadyExists(user.getLogin()));

    string password;
    cout << "Please enter the password: ";
    password = AuxiliaryMethods::loadLine();
    user.setPassword(password);

    string name;
    cout << "Please enter your name: ";
    name = AuxiliaryMethods::loadLine();
    user.setName(name);

    string surname;
    cout << "Please enter your surname: ";
    surname = AuxiliaryMethods::loadLine();
    user.setSurname(surname);

    return user;
}

int UserManager::getIdOfNewUser() {
    if (users.empty())
        return 1;
    else
        return users.back().getUserId() + 1;
}

void UserManager::registerUser() {
    User user = enterNewUserData();

    users.push_back(user);
    userFile.addUserToFile(user);

    cout << endl << "The user account has been successfully created" << endl << endl;
}

int UserManager::login() {
    string login = "", password = "";

    cout << endl << "Please enter your login: ";
    login = AuxiliaryMethods::loadLine();

    int i = 0;
    while (i < users.size()) {
        if (users[i].getLogin() == login) {
            for (int numberOfAttempts = 3; numberOfAttempts > 0; numberOfAttempts--) {
                cout << "Please enter the password. Attempts left: " << numberOfAttempts << ": ";
                password = AuxiliaryMethods::loadLine();

                if (users[i].getPassword() == password) {
                    loggedInUserId = users[i].getUserId();
                    cout << endl << "Hello "<< users[i].getName() << "! You are logged in." << endl << endl;

                    return loggedInUserId;
                }
            }
            cout << "You entered the password 3 times incorrectly." << endl;
        }
        i++;
    }
    /*cout << "There is no user with this login" << endl << endl;
    system("pause");
    return 0;*/   /// zle napisane, zle miejsce
}

void UserManager::changePasswordOfLoggedInUser() {
    string newPassword = "";
    cout << "Please enter a new password: ";
    newPassword = AuxiliaryMethods::loadLine();

    for (int i = 0; i < users.size(); i++) {
        if (users[i].getUserId() == loggedInUserId) {
            users[i].setPassword(newPassword);
            cout << "Password changed." << endl << endl;

            userFile.saveNewPasswordToFile(users[i]);
        }
    }
}

void UserManager::logout() {
    loggedInUserId = 0;
}

bool UserManager::checkThatUserIsLoggedIn() {
    if (loggedInUserId > 0)
        return true;
    else
        return false;
}

int UserManager::getIdOfLoggedInUser() {
    return loggedInUserId;
}

vector <User> UserManager::loadUsersFromFile() {
    userFile.loadUsersFromFile();
}





