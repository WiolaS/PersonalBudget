#include <iostream>
#include <windows.h>
#include <sstream>
#include "CashFlow.h"

using namespace std;

void CashFlow::setCashFlowId(int CASH_FLOW_ID) {
    cashFlowId = CASH_FLOW_ID;
}
void CashFlow::setUserId (int USER_ID) {
    userId = USER_ID;
}
void CashFlow::setDate (string DATE) {
    date = DATE;
}
void CashFlow::setItem (string ITEM) {
    item = ITEM;
}
void CashFlow::setAmount (float AMOUNT) {
    amount = AMOUNT;
}

int CashFlow::getCashFlowId() {
    return cashFlowId;
}
int CashFlow::getUserId() {
    return userId;
}
string CashFlow::getDate() {
    return date;
}
string CashFlow::getItem() {
    return item;
}
float CashFlow::getAmount() {
    return amount;
}

