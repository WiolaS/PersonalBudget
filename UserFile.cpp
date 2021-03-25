#include "UserFile.h"
#include "AuxiliaryMethods.h"
#include <windows.h>
#include <fstream>

using namespace std;

void UserFile::setNumberOfLoadedUsers (int newNumberOfLoadedUsers) {
    numberOfLoadedUsers = newNumberOfLoadedUsers;
}

int UserFile::getNumberOfLoadedUsers() {
    return numberOfLoadedUsers;
}

void UserFile::addUserToFile(User user) {
    int numberOfUsers = getNumberOfLoadedUsers();
    string strNumberOfUsers = AuxiliaryMethods::convertIntToString(numberOfUsers);
    int numberOfParameters = 5;

    CMarkup xml;

    if (numberOfLoadedUsers == 0) {
        xml.AddElem("users");
        xml.IntoElem();
        xml.AddElem("userId", numberOfUsers + 1);
        xml.AddElem( "login", user.getLogin());
        xml.AddElem( "password", user.getPassword());
        xml.AddElem( "name", user.getName());
        xml.AddElem( "surname", user.getSurname());
        xml.Save("users.xml");
        xml.OutOfElem(); // back out level
    } else {
        bool bSuccess = xml.Load( "users.xml" );
        xml.ResetPos(); // top of document
        xml.FindElem(); // users element is root
        xml.IntoElem(); // inside users
        while ( xml.FindElem("userId") ) {
            if ( xml.GetData() == strNumberOfUsers ) {
                for (int i = 0; i < numberOfParameters; i++) {
                    xml.FindElem();
                }
                xml.AddElem("userId", numberOfUsers + 1);
                xml.AddElem( "login", user.getLogin());
                xml.AddElem( "password", user.getPassword());
                xml.AddElem( "name", user.getName());
                xml.AddElem( "surname", user.getSurname());

                xml.Save("users.xml");
                xml.OutOfElem(); // back out level
            }
        }
    }
    setNumberOfLoadedUsers(numberOfUsers + 1);
}

vector <User> UserFile::loadUsersFromFile() {
    User user;
    vector <User> users;

    CMarkup xml;
    bool bSuccess = xml.Load( "users.xml" );
    xml.ResetPos(); // top of document
    xml.FindElem(); // users element is root
    xml.IntoElem(); // inside users

    while ( xml.FindElem("userId") ) {
        setNumberOfLoadedUsers(AuxiliaryMethods::convertStringToInt(xml.GetData()));
        user.setUserId(AuxiliaryMethods::convertStringToInt(xml.GetData()));

        xml.FindElem("login");
        user.setLogin(xml.GetData());

        xml.FindElem("password");
        user.setPassword(xml.GetData());

        xml.FindElem("name");
        user.setName(xml.GetData());

        xml.FindElem("surname");
        user.setSurname(xml.GetData());

        users.push_back(user);
    }
    return users;
}


void UserFile::saveNewPasswordToFile(User user) {

    string strUserId = AuxiliaryMethods::convertIntToString(user.getUserId());
    CMarkup xml;

    bool bSuccess = xml.Load( "users.xml" );
    xml.ResetPos(); // top of document
    xml.FindElem(); // users element is root
    xml.IntoElem(); // inside users

    while ( xml.FindElem("userId") ) {
        if ( xml.GetData() == strUserId ) {
            if ( xml.FindElem("password") ) {
                xml.SetData (user.getPassword());
            }
        }
    }
    xml.Save("users.xml");
    xml.OutOfElem(); // back out level
}


