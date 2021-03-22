#ifndef INCOMEFILE_H
#define INCOMEFILE_H
#include <iostream>
#include <vector>
#include "CashFlow.h"
#include "TextFile.h"
#include "Markup.h"

using namespace std;

class IncomeFile : public TextFile {

    int idOfTheLastIncome;

public:
    IncomeFile (string incomeFileName): TextFile (incomeFileName)  {
        idOfTheLastIncome = 0;
    }

    void addIncomeToFile(CashFlow income);
    vector <CashFlow> loadIncomesOfTheLoggedinUserFromTheFile(int logedInUserId);
    void setNumberOfLoadedIncomes (int numberOfLoadedIncomes);
    int getNumberOfLoadedIncomes();
};

#endif // INCOMEFILE
