#ifndef DATE_H
#define DATE_H
#include <iostream>

using namespace std;

class Date {
    int year;
    int month;
    int day;

public:
    Date(int year = 0, int month = 0, int day = 0) {
        this->year  = year;
        this->month = month;
        this->day = day;
    }

    ///settery
    void setYear (int year);
    void setMonth (int month);
    void setDay (int day);

    ///gettery
    int getYear();
    int getMonth();
    int getDay();

};

#endif // DATE
