#include "IncomeFile.h"
#include "AuxiliaryMethods.h"
#include <windows.h>
#include <fstream>

using namespace std;

void IncomeFile::setNumberOfLoadedIncomes (int numberOfLoadedIncomes) {
    idOfTheLastIncome = numberOfLoadedIncomes;
}

int IncomeFile::getNumberOfLoadedIncomes() {
    return idOfTheLastIncome;
}

void IncomeFile::addIncomeToFile(CashFlow income) {
    int numberOfIncomes = getNumberOfLoadedIncomes();
    string strNumberOfIncomes = AuxiliaryMethods::convertIntToString(numberOfIncomes);
    int numberOfParameters = 5;

    CMarkup xml;
    if (numberOfIncomes == 0) {
        xml.AddElem("incomes");
        xml.IntoElem();
        xml.AddElem("incomeId", numberOfIncomes + 1);  ///check
        xml.AddElem( "userId", income.getUserId());
        xml.AddElem( "date", income.getDate());
        xml.AddElem( "item", income.getItem());
        xml.AddElem( "amount", AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces(income.getAmount()));
        xml.Save("incomes.xml");
        xml.OutOfElem(); // back out level
    } else {
        bool bSuccess = xml.Load("incomes.xml");
        xml.ResetPos(); // top of document
        xml.FindElem(); // users element is root
        xml.IntoElem(); // inside users
        while ( xml.FindElem("incomeId") ) {
            if ( xml.GetData() == strNumberOfIncomes ) {
                for (int i = 0; i < numberOfParameters; i++) {
                    xml.FindElem();
                }
                xml.AddElem("incomeId", numberOfIncomes + 1);
                xml.AddElem( "userId", income.getUserId());
                xml.AddElem( "date", income.getDate());
                xml.AddElem( "item", income.getItem());
                xml.AddElem( "amount", AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces(income.getAmount()));
                xml.Save("incomes.xml");
                xml.OutOfElem(); // back out level
            }
        }
    }
    setNumberOfLoadedIncomes( numberOfIncomes + 1);
}


vector <CashFlow> IncomeFile::loadIncomesOfTheLoggedinUserFromTheFile(int logedInUserId) {
    CashFlow income;
    vector <CashFlow> incomes;

    CMarkup xml;
    bool bSuccess = xml.Load("incomes.xml");
    xml.ResetPos(); // top of document
    xml.FindElem(); // users element is root
    xml.IntoElem(); // inside users

    while ( xml.FindElem("incomeId") ) {
        setNumberOfLoadedIncomes(AuxiliaryMethods::convertStringToInt(xml.GetData()));
        income.setCashFlowId(AuxiliaryMethods::convertStringToInt(xml.GetData()));

        xml.FindElem("userId");
        income.setUserId(AuxiliaryMethods::convertStringToInt(xml.GetData()));

        xml.FindElem("date");
        income.setDate(xml.GetData());

        xml.FindElem("item");
        income.setItem(xml.GetData());

        xml.FindElem("amount");
        income.setAmount(AuxiliaryMethods::convertStringToFloat(xml.GetData()));

        incomes.push_back(income);
    }
    return incomes;

}

