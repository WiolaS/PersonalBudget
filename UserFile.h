#ifndef USERFILE_H
#define USERFILE_H
#include <iostream>
#include <vector>
#include "User.h"
#include "TextFile.h"
#include "Markup.h"

using namespace std;

class UserFile : public TextFile {

    int numberOfLoadedUsers;

    User getUserData();
    void checkTheNumberOfLoadedUsers ();

public:
    UserFile(string fileName, int NUMBEROFLOADEDUSERS = 0) : TextFile(fileName), numberOfLoadedUsers(NUMBEROFLOADEDUSERS) {
        this->numberOfLoadedUsers = NUMBEROFLOADEDUSERS;
    };

    void setNumberOfLoadedUsers (int numberOfLoadedUsers);
    int getNumberOfLoadedUsers();
    void addUserToFile(User);
    void saveAllUsersToFile(vector <User> &users);
    vector <User> loadUsersFromFile();
    void saveNewPasswordToFile(User user);

};

#endif // USERFILE




