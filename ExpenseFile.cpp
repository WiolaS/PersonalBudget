#include "ExpenseFile.h"
#include "AuxiliaryMethods.h"
#include <windows.h>
#include <fstream>

using namespace std;

void ExpenseFile::setNumberOfLoadedExpenses (int numberOfLoadedExpenses) {
    idOfTheLastExpense = numberOfLoadedExpenses;
}

int ExpenseFile::getNumberOfLoadedExpenses() {
    return idOfTheLastExpense;
}

void ExpenseFile::addExpenseToFile(CashFlow expense) {
    int numberOfExpenses = getNumberOfLoadedExpenses();

    string numberOfExpensesInStringNotation = AuxiliaryMethods::convertIntToString(numberOfExpenses);
    int numberOfParameters = 5;

    CMarkup xml;

    if (numberOfExpenses == 0) {
        xml.AddElem("expenses");
        xml.IntoElem();
        xml.AddElem("expenseId", numberOfExpenses + 1);  ///check
        xml.AddElem( "userId", expense.getUserId());
        xml.AddElem( "date", expense.getDate());
        xml.AddElem( "item", expense.getItem());
        xml.AddElem( "amount", AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces(expense.getAmount()));
        xml.Save("C:\\Users\\wiole\\Desktop\\GitHub_nauka\\PersonalBudgetWiola\\expenses.xml");
        xml.OutOfElem(); // back out level

    } else {
        bool bSuccess = xml.Load( "C:\\Users\\wiole\\Desktop\\GitHub_nauka\\PersonalBudgetWiola\\expenses.xml" );
        xml.ResetPos(); // top of document
        xml.FindElem(); // users element is root
        xml.IntoElem(); // inside users
        while ( xml.FindElem("expenseId") ) {
            if ( xml.GetData() == numberOfExpensesInStringNotation ) {
                for (int i = 0; i < numberOfParameters; i++) {
                    xml.FindElem();
                }
                xml.AddElem("expenseId", numberOfExpenses + 1);
                xml.AddElem( "userId", expense.getUserId());
                xml.AddElem( "date", expense.getDate());
                xml.AddElem( "item", expense.getItem());
                xml.AddElem( "amount", AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces(expense.getAmount()));

                xml.Save("C:\\Users\\wiole\\Desktop\\GitHub_nauka\\PersonalBudgetWiola\\expenses.xml");
                xml.OutOfElem(); // back out level
            }
        }
    }
    setNumberOfLoadedExpenses( numberOfExpenses + 1);
}


vector <CashFlow> ExpenseFile::loadExpensesOfTheLoggedinUserFromTheFile(int logedInUserId) {
    CashFlow expense;
    vector <CashFlow> expenses;

    CMarkup xml;
    bool bSuccess = xml.Load( "C:\\Users\\wiole\\Desktop\\GitHub_nauka\\PersonalBudgetWiola\\expenses.xml" );
    xml.ResetPos(); // top of document
    xml.FindElem(); // users element is root
    xml.IntoElem(); // inside users

    while ( xml.FindElem("expenseId") ) {
        setNumberOfLoadedExpenses(AuxiliaryMethods::convertStringToInt(xml.GetData()));
        expense.setCashFlowId(AuxiliaryMethods::convertStringToInt(xml.GetData()));

        xml.FindElem("userId");
        expense.setUserId(AuxiliaryMethods::convertStringToInt(xml.GetData()));

        xml.FindElem("date");
        expense.setDate(xml.GetData());

        xml.FindElem("item");
        expense.setItem(xml.GetData());

        xml.FindElem("amount");
        expense.setAmount(AuxiliaryMethods::convertStringToFloat(xml.GetData()));

        expenses.push_back(expense);
    }
    return expenses;

}

