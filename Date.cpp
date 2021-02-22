#include <iostream>
#include "Date.h"

using namespace std;

void Date::setYear (int YEAR) {
    year = YEAR;
}
void Date::setMonth (int MONTH) {
    month = MONTH;
}
void Date::setDay (int DAY) {
    day = DAY;
}

int Date::getYear() {
    return year;
}
int Date::getMonth() {
    return month;
}
int Date::getDay() {
    return day;
}

