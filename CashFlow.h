#ifndef CASHFLOW_H
#define CASHFLOW_H
#include <iostream>
#include "Date.h"  // replace - DateManager

using namespace std;

class CashFlow {
    int cashFlowId;
    int userId;
    string date;
    string item;
    float amount;

    //vector <Date> dates;  // is it necessary?



public:
    CashFlow(int cashFlowId = 0, int userId = 0, string date = "", string item = "", float amount = 0) {
        this->cashFlowId = cashFlowId;
        this->userId = userId;
        this->date = date;
        this->item = item;
        this->amount = amount;
    }

    ///settery
    void setCashFlowId (int cashFlowId);
    void setUserId (int userId);
    void setDate (string date);
    void setItem (string item);
    void setAmount (float amount);

    ///gettery
    int getCashFlowId();
    int getUserId();
    string getDate();
    string getItem();
    float getAmount();
};

#endif // CASHFLOW

