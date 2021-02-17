#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <iostream>
#include <vector>
#include "User.h"
#include "UserFile.h"

using namespace std;

class UserManager {

    int loggeInUserId;
    vector <User> users;
    UserFile userFile;

    User enterNewUserData();
    int getIdOfNewUser();
    bool checkIfSuchLoginAlreadyExists(string login);

public:

    UserManager (string userFileName) : userFile (userFileName) {
        loggeInUserId = 0;
        users = userFile.loadUsersFromFile();
    };

    void registerUser();
    int login();
    void changePasswordOfLoggedInUser();
    void logout();
    bool checkThatUserIsLoggedIn();
    int getIdOfLoggedInUser();
    vector <User> loadUsersFromFile();
};

#endif // USERMANAGER


