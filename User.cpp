#include <iostream>
#include "User.h"

using namespace std;

void User::setUserId(int USER_ID) {
    userId = USER_ID;
}
void User::setLogin (string LOGIN) {
    login = LOGIN;
}
void User::setPassword (string PASSWORD) {
    password = PASSWORD;
}
void User::setName (string NAME) {
    name = NAME;
}
void User::setSurname (string SURNAME) {
    surname = SURNAME;
}

int User::getUserId() {
    return userId;
}
string User::getLogin() {
    return login;
}
string User::getPassword() {
    return password;
}
string User::getName() {
    return name;
}
string User::getSurname() {
    return surname;
}
