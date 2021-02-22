#ifndef EXPENSEFILE_H
#define EXPENSEFILE_H
#include <iostream>
#include <vector>
#include "CashFlow.h"
#include "TextFile.h"
#include "Markup.h"

using namespace std;

class ExpenseFile : public TextFile {

    int idOfTheLastExpense;

public:
    ExpenseFile (string expenseFileName): TextFile (expenseFileName)  {
        idOfTheLastExpense = 0;
    }

    void addExpenseToFile(CashFlow income);
    vector <CashFlow> loadExpensesOfTheLoggedinUserFromTheFile(int logedInUserId);

    void setNumberOfLoadedExpenses (int numberOfLoadedIncomes);
    int getNumberOfLoadedExpenses();
};

#endif // EXPENSEFILE


