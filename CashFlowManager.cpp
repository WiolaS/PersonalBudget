#include "CashFlowManager.h"
#include "AuxiliaryMethods.h"
#include <iomanip>      // setprecision

using namespace std;

Date CashFlowManager::getDateFromTheSystem () {
    Date date;
    SYSTEMTIME st;
    GetSystemTime(&st);

    date.setYear(st.wYear);
    date.setMonth(st.wMonth);
    date.setDay(st.wDay);

    return date;
}


string CashFlowManager::combineDateElementsIntoAString(int year, int month, int day) {
    string stdate = "";
    string stYear = AuxiliaryMethods::convertIntToString (year);
    string stMonth = AuxiliaryMethods::convertIntToString (month);
    string stDay = AuxiliaryMethods::convertIntToString (day);

    if (month < 10) {
        stMonth = "0" + AuxiliaryMethods::convertIntToString (month);
    }
    if (day < 10) {
        stDay = "0" + AuxiliaryMethods::convertIntToString (day);
    }

    stdate = stYear + "-" + stMonth + "-" + stDay;

    return stdate;
}

string CashFlowManager::replaceDateElementsWithASingleString (Date date) {
    string stDate = combineDateElementsIntoAString(date.getYear(), date.getMonth(), date.getDay());
    return stDate;
}


Date CashFlowManager::splitTheDateFromTheStringIntoIndividualElements (string dateEnteredByTheUser) {
    Date date;
    string dateElement = "";
    int singleDateNumber = 1;

    for (int datePosition = 0; datePosition < dateEnteredByTheUser.length(); datePosition++) {
        if (dateEnteredByTheUser[datePosition] != '-') {
            dateElement += dateEnteredByTheUser[datePosition];
        } else {
            switch(singleDateNumber) {
            case 1:
                date.setYear(atoi(dateElement.c_str()));
                break;
            case 2:
                date.setMonth(atoi(dateElement.c_str()));
                break;
            case 3:
                date.setDay(atoi(dateElement.c_str()));
                break;
            }
            dateElement = "";
            singleDateNumber++;
        }
    }

    return date;
}



bool CashFlowManager::checkIfTheYearIsALeapYear (int year) {
    if (year % 4 == 0)
        return true;
    else
        return false;
}

int CashFlowManager::checkHowManyDaysAMonthHas (int month, int year) {
    int numberOfDaysOfTheMonth = 0;

    if ((month % 2 != 0 && month < 8) || (month % 2 == 0 && month > 7)) {
        numberOfDaysOfTheMonth = 31;
    } else if (month == 2) {
        if (checkIfTheYearIsALeapYear(year)) {
            numberOfDaysOfTheMonth = 29;
        } else
            numberOfDaysOfTheMonth = 28;
    } else
        numberOfDaysOfTheMonth = 30;

    return numberOfDaysOfTheMonth;
}


bool CashFlowManager::checkIfTheYearNumberIsCorrect (Date dateEnteredByTheUser, Date currentDate) {

    if(dateEnteredByTheUser.getYear() >= 2000 && dateEnteredByTheUser.getYear() <= currentDate.getYear()) {
        return true;
    } else
        return false;
}

bool CashFlowManager::checkIfTheDayNumberIsCorrect (Date dateEnteredByTheUser, Date currentDate) {
    if (dateEnteredByTheUser.getDay() >= 1 && dateEnteredByTheUser.getDay() <= checkHowManyDaysAMonthHas (dateEnteredByTheUser.getMonth(), dateEnteredByTheUser.getYear()))
        return true;
    else
        return false;
}


bool CashFlowManager::checkIfTheMonthNumberWithTheDayNumberAreCorrect (Date dateEnteredByTheUser, Date currentDate) {

    int numberOfTheFirstMonthOfTheYear = 1;
    int numberOfTheLastMonthOfTheYear = 12;

    if (dateEnteredByTheUser.getYear() == currentDate.getYear()) {
        if(dateEnteredByTheUser.getMonth() >= numberOfTheFirstMonthOfTheYear && dateEnteredByTheUser.getMonth() <= currentDate.getMonth()) {
            if (checkIfTheDayNumberIsCorrect(dateEnteredByTheUser, currentDate))
                return true;
            else
                return false;
        } else
            return false;
    } else {
        if  (dateEnteredByTheUser.getMonth() >= numberOfTheFirstMonthOfTheYear && dateEnteredByTheUser.getMonth() <= numberOfTheLastMonthOfTheYear) {
            if (checkIfTheDayNumberIsCorrect(dateEnteredByTheUser, currentDate))
                return true;
            else
                return false;
        } else
            return false;
    }
}

bool CashFlowManager::checkTheCorrectnesOfTheEnteredDate (Date dateEnteredByTheUser, Date currentDate) {

    if(checkIfTheYearNumberIsCorrect(dateEnteredByTheUser, currentDate) == true) {
        if(checkIfTheMonthNumberWithTheDayNumberAreCorrect(dateEnteredByTheUser, currentDate) == true)
            return true;
        else {
            return false;
        }
    } else
        return false;
}


string CashFlowManager::enterTheNewDate (Date currentDate) {
    string dateEnteredByTheUser;
    Date dateEnteredByTheUserInNumberFormat;

    cout << "Please enter date in the format yyyy-mm-dd: ";

    dateEnteredByTheUser = AuxiliaryMethods::loadLine();
    dateEnteredByTheUserInNumberFormat = splitTheDateFromTheStringIntoIndividualElements(dateEnteredByTheUser + "-");

    if (checkTheCorrectnesOfTheEnteredDate(dateEnteredByTheUserInNumberFormat, currentDate) == true)
        return dateEnteredByTheUser;
    else {
        cout << endl << "Please also note that the date should be in the range of" << endl;
        cout << "2000-01-01 to the last day of the current month: " << endl;
        dateEnteredByTheUser = enterTheNewDate (currentDate);
    }
}

string CashFlowManager::setTheDateOfTheCashFlow (string typeOfCashFlow) {

    string dateEnteredByTheUser;
    Date currentDateInNumberFormat;
    string dateOfTheCashFlow;
    char choice;
    CashFlow cashFlow;

    currentDateInNumberFormat = getDateFromTheSystem ();
    choice = AuxiliaryMethods::selectAnOptionFromTheCashFlowMenu(typeOfCashFlow);

    switch (choice) {
    case '1':
        dateOfTheCashFlow = replaceDateElementsWithASingleString (currentDateInNumberFormat);
        system("pause");
        break;
    case '2':

        dateEnteredByTheUser = enterTheNewDate(currentDateInNumberFormat);
        dateOfTheCashFlow = dateEnteredByTheUser;

        system("pause");
        break;
    default:
        cout << endl << "There is no such option on the menu." << endl << endl;
        system("pause");
        break;

    }
    return dateOfTheCashFlow;
}


string CashFlowManager::enterTheItemOfCashFlow() {
    string itemDescribingTheCashFlow;

    cout << "Enter an item describing the cash flow: ";
    itemDescribingTheCashFlow = AuxiliaryMethods::loadLine();

    return itemDescribingTheCashFlow;
}



float CashFlowManager::enterTheAmountOfCashFlow() {
    string enteredAmountInStringformat;
    string decimalAmountSeparatedByADot;
    string correctedAmountToTwoDecimalPlaces;
    float amountOfCashFlowInNumberFormat;

    cout << "Enter the cash flow amount: ";
    enteredAmountInStringformat = AuxiliaryMethods::loadLine();
    if (enteredAmountInStringformat == "") {
        decimalAmountSeparatedByADot = "0";
    } else {
        decimalAmountSeparatedByADot = AuxiliaryMethods::checkIfThereIsAComma(enteredAmountInStringformat);
    }
    amountOfCashFlowInNumberFormat = AuxiliaryMethods::convertStringToFloat(decimalAmountSeparatedByADot);
    correctedAmountToTwoDecimalPlaces = AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces(amountOfCashFlowInNumberFormat);
    amountOfCashFlowInNumberFormat = AuxiliaryMethods::convertStringToFloat(correctedAmountToTwoDecimalPlaces);

    return amountOfCashFlowInNumberFormat;
}

CashFlow CashFlowManager::addCashFlow(string typeOfCashFlow) {
    CashFlow cashFlow;

    cashFlow.setCashFlowId(1); // to change
    cashFlow.setUserId(LOGGED_IN_USER_ID);
    cashFlow.setDate(setTheDateOfTheCashFlow(typeOfCashFlow));
    cashFlow.setItem(enterTheItemOfCashFlow());
    cashFlow.setAmount(enterTheAmountOfCashFlow());

    cout << cashFlow.getCashFlowId() << endl;
    cout << cashFlow.getUserId() << endl;
    cout << cashFlow.getDate() << endl;
    cout << cashFlow.getItem() << endl;
    cout << cashFlow.getAmount() << endl;

    system("pause");

    return cashFlow;
}



int CashFlowManager::addIncome () {

    CashFlow income;
    string typeOfCashFlow = "income";

    system("cls");
    income = addCashFlow(typeOfCashFlow);

    incomes.push_back(income);
    incomeFile.addIncomeToFile(income);

}

void CashFlowManager::sortIncomesByDate() {

    CashFlow temp;
    Date date1;
    Date date2;

    for (int i = 0; i < incomes.size() -1; i++) {
        {
            for (int j=i+1; j<incomes.size(); j++) {
                date1 = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");
                date2 = splitTheDateFromTheStringIntoIndividualElements(incomes[j].getDate() + "-");
                if (date1.getYear() > date2.getYear()) {
                    temp = incomes[i];
                    incomes[i] = incomes[j];
                    incomes[j] = temp;
                } else if (date1.getYear() == date2.getYear() && date1.getMonth() > date2.getMonth()) {
                    temp = incomes[i];
                    incomes[i] = incomes[j];
                    incomes[j] = temp;
                } else if (date1.getYear() == date2.getYear() && date1.getMonth() == date2.getMonth() && date1.getDay() > date2.getDay()) {
                    temp = incomes[i];
                    incomes[i] = incomes[j];
                    incomes[j] = temp;
                }

            }
        }
    }
}

void CashFlowManager::sortExpensesByDate() {

    CashFlow temp;
    Date date1;
    Date date2;

    for (int i = 0; i < expenses.size() -1; i++) {
        {
            for (int j=i+1; j<expenses.size(); j++) {
                date1 = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
                date2 = splitTheDateFromTheStringIntoIndividualElements(expenses[j].getDate() + "-");
                if (date1.getYear() > date2.getYear()) {
                    temp = expenses[i];
                    expenses[i] = expenses[j];
                    expenses[j] = temp;
                } else if (date1.getYear() == date2.getYear() && date1.getMonth() > date2.getMonth()) {
                    temp = expenses[i];
                    expenses[i] = expenses[j];
                    expenses[j] = temp;
                } else if (date1.getYear() == date2.getYear() && date1.getMonth() == date2.getMonth() && date1.getDay() > date2.getDay()) {
                    temp = expenses[i];
                    expenses[i] = expenses[j];
                    expenses[j] = temp;
                }

            }
        }
    }
}


int CashFlowManager::addExpense () {

    CashFlow expense;
    string typeOfCashFlow = "income";

    system("cls");
    expense = addCashFlow(typeOfCashFlow);

    expenses.push_back(expense);
    expenseFile.addExpenseToFile(expense);

}


string CashFlowManager::changTheFloatTypeToStringOfLength12 (float amountOfCasfFlow) {
    string amountInStringNotation = "";
    int lengthOfString = 0;

    amountInStringNotation = AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces(amountOfCasfFlow);
    lengthOfString = amountInStringNotation.length();

    lengthOfString = amountInStringNotation.length();

    while (lengthOfString < 12) {
        amountInStringNotation.insert(0," ");
        lengthOfString = amountInStringNotation.length();
    }

    return amountInStringNotation;
}


void CashFlowManager::showTheTotalAmountOfCashFlows (float sumOfIncomes, float sumOfExpenses) {
    float amountOfTheDifferenceBetweenIncomeAndExpense;
    string sumOfIncomesInStringNotation = "";
    string sumOfExpensesInStringNotation = "";
    string balance = "";

    if (sumOfIncomes >= sumOfExpenses) {
        amountOfTheDifferenceBetweenIncomeAndExpense = sumOfIncomes - sumOfExpenses;
    } else
        amountOfTheDifferenceBetweenIncomeAndExpense = sumOfExpenses - sumOfIncomes;

    sumOfIncomesInStringNotation = changTheFloatTypeToStringOfLength12 (sumOfIncomes);
    sumOfExpensesInStringNotation = changTheFloatTypeToStringOfLength12 (sumOfExpenses);
    balance = changTheFloatTypeToStringOfLength12 (amountOfTheDifferenceBetweenIncomeAndExpense);

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Total amount of incomes:  " << fixed <<setprecision(2) << sumOfIncomesInStringNotation << " PLN" << endl;
    cout << "Total amount of expenses: " << fixed <<setprecision(2) << sumOfExpensesInStringNotation << " PLN" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Balance:                  " << balance  << " PLN" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    system("pause");

}

float CashFlowManager::calculateTheSumOfIncomesForTheCurrentMonth() {
    Date dateInDateFormat;
    Date currentDate = getDateFromTheSystem();
    float amountOfIncomesFromTheCurrentMonth = 0;
    string amountInStringNotation = "";
    string typeOfcashFlow = "Incomes";

    sortIncomesByDate();
    system("cls");
    AuxiliaryMethods::AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);

    for (int i = 0; i < incomes.size(); i++) {
        dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");
        if (currentDate.getYear() == dateInDateFormat.getYear() && currentDate.getMonth() == dateInDateFormat.getMonth() )  {

            amountInStringNotation = changTheFloatTypeToStringOfLength12 (incomes[i].getAmount());
            amountOfIncomesFromTheCurrentMonth += incomes[i].getAmount();
            cout << "|" << incomes[i].getDate() << " |" << amountInStringNotation << " |" << "   PLN   |" << incomes[i].getItem() << endl;
        }
    }
    return amountOfIncomesFromTheCurrentMonth;
}

float CashFlowManager::calculateTheSumOfExpensesForTheCurrentMonth() {
    Date dateInDateFormat;
    Date currentDate = getDateFromTheSystem();
    float amountOfExpensesFromTheCurrentMonth = 0;
    string amountInStringNotation = "";
    string typeOfcashFlow = "Expenses";

    sortExpensesByDate();
    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);

    for (int i = 0; i < expenses.size(); i++) {
        dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
        if (currentDate.getYear() == dateInDateFormat.getYear() && currentDate.getMonth() == dateInDateFormat.getMonth())  {

            amountInStringNotation = changTheFloatTypeToStringOfLength12 (expenses[i].getAmount());
            amountOfExpensesFromTheCurrentMonth += expenses[i].getAmount();
            cout << "|" << expenses[i].getDate() << " |" << amountInStringNotation << " |" << "   PLN   |" << expenses[i].getItem() << endl;
        }
    }
    return amountOfExpensesFromTheCurrentMonth;
}


void CashFlowManager::showTheBalanceSheetOfTheCurrentMonth() {
    float sumOfIncomes = calculateTheSumOfIncomesForTheCurrentMonth();
    float sumOfExpenses = calculateTheSumOfExpensesForTheCurrentMonth();

    showTheTotalAmountOfCashFlows (sumOfIncomes, sumOfExpenses);
}

float CashFlowManager::calculateTheSumOfIncomesForThePreviousMonth() {
    Date dateInDateFormat;
    Date currentDate = getDateFromTheSystem ();
    int numberOfTheFirstMonthOfTheYear = 1;
    int numberOfTheLasttMonthOfTheYear = 12;
    float amountOfIncomesFromThePreviousMonth = 0;
    string amountInStringNotation = "";
    string typeOfcashFlow = "Incomes";

    sortIncomesByDate();
    system("cls");
    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);

    for (int i = 0; i < incomes.size(); i++) {
        dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");

        if ((currentDate.getYear() == dateInDateFormat.getYear() && currentDate.getMonth() == (dateInDateFormat.getMonth() + 1)) ||
                (currentDate.getYear() == (dateInDateFormat.getYear() + 1) && (currentDate.getMonth() == numberOfTheFirstMonthOfTheYear &&
                        dateInDateFormat.getMonth() == numberOfTheLasttMonthOfTheYear)))  {

            amountInStringNotation = changTheFloatTypeToStringOfLength12 (incomes[i].getAmount());
            amountOfIncomesFromThePreviousMonth += incomes[i].getAmount();
            cout << "|" << incomes[i].getDate() << " |" << amountInStringNotation << " |" << "   PLN   |" << incomes[i].getItem() << endl;
        }
    }
    return amountOfIncomesFromThePreviousMonth;
}






float CashFlowManager::calculateTheSumOfExpensesForThePreviousMonth() {
    Date dateInDateFormat;
    Date currentDate = getDateFromTheSystem();
    int numberOfTheFirstMonthOfTheYear = 1;
    int numberOfTheLasttMonthOfTheYear = 12;
    float amountOfExpensesFromThePreviousMonth = 0;
    string amountInStringNotation = "";
    string typeOfcashFlow = "Expenses";

    sortExpensesByDate();
    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);

    for (int i = 0; i < expenses.size(); i++) {
        dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
        if ((currentDate.getYear() == dateInDateFormat.getYear() && currentDate.getMonth() == (dateInDateFormat.getMonth() + 1)) ||
                (currentDate.getYear() == (dateInDateFormat.getYear() + 1) && (currentDate.getMonth() == numberOfTheFirstMonthOfTheYear &&
                        dateInDateFormat.getMonth() == numberOfTheLasttMonthOfTheYear)))  {

            amountInStringNotation = changTheFloatTypeToStringOfLength12 (expenses[i].getAmount());
            amountOfExpensesFromThePreviousMonth += expenses[i].getAmount();
            cout << "|" << expenses[i].getDate() << " |" << amountInStringNotation << " |" << "   PLN   |" << expenses[i].getItem() << endl;
        }
    }
    return amountOfExpensesFromThePreviousMonth;
}

void CashFlowManager::showTheBalanceSheetOfThePrevoiusMonth() {
    float sumOfIncomes = calculateTheSumOfIncomesForThePreviousMonth();
    float sumOfExpenses = calculateTheSumOfExpensesForThePreviousMonth();

    showTheTotalAmountOfCashFlows (sumOfIncomes, sumOfExpenses);
}

float CashFlowManager::calculateTheSumOfIncomesForTheSelectedPeriod(Date startDate, Date endDate) {
    Date dateInDateFormat;
    Date currentDateInNumberFormat = getDateFromTheSystem();
    float amountOfIncomesFromTheSelectedPeriod = 0;
    string amountInStringNotation = "";
    string typeOfcashFlow = "Incomes";

    sortIncomesByDate();
    system("cls");
    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);

    for (int i = 0; i < incomes.size(); i++) {
        dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");

        if ((startDate.getYear() < dateInDateFormat.getYear() ||
                startDate.getYear() == dateInDateFormat.getYear() && startDate.getMonth() < dateInDateFormat.getMonth() ||
                startDate.getYear() == dateInDateFormat.getYear() && startDate.getMonth() == dateInDateFormat.getMonth() && startDate.getDay() <= dateInDateFormat.getDay()) &&

                (endDate.getYear() > dateInDateFormat.getYear() ||
                 endDate.getYear() == dateInDateFormat.getYear() && endDate.getMonth() > dateInDateFormat.getMonth() ||
                 endDate.getYear() == dateInDateFormat.getYear() && endDate.getMonth() == dateInDateFormat.getMonth() && endDate.getDay() >= dateInDateFormat.getDay())) {

            amountInStringNotation = changTheFloatTypeToStringOfLength12 (incomes[i].getAmount());
            amountOfIncomesFromTheSelectedPeriod += incomes[i].getAmount();
            cout << "|" << incomes[i].getDate() << " |" << amountInStringNotation << " |" << "   PLN   |" << incomes[i].getItem() << endl;
        }
    }
    return amountOfIncomesFromTheSelectedPeriod;
}


float CashFlowManager::calculateTheSumOfExpensesForTheSelectedPeriod(Date startDate, Date endDate) {

    Date dateInDateFormat;
    float amountOfExpensesFromTheSelectedPeriod = 0;
    string amountInStringNotation = "";
    int lengthOfString = 0;
    string typeOfcashFlow = "Expenses";

    sortExpensesByDate();
    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);

    for (int i = 0; i < expenses.size(); i++) {
        dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
        if ((startDate.getYear() < dateInDateFormat.getYear() ||
                startDate.getYear() == dateInDateFormat.getYear() && startDate.getMonth() < dateInDateFormat.getMonth() ||
                startDate.getYear() == dateInDateFormat.getYear() && startDate.getMonth() == dateInDateFormat.getMonth() && startDate.getDay() <= dateInDateFormat.getDay()) &&

                (endDate.getYear() > dateInDateFormat.getYear() ||
                 endDate.getYear() == dateInDateFormat.getYear() && endDate.getMonth() > dateInDateFormat.getMonth() ||
                 endDate.getYear() == dateInDateFormat.getYear() && endDate.getMonth() == dateInDateFormat.getMonth() && endDate.getDay() >= dateInDateFormat.getDay())) {

            amountInStringNotation = changTheFloatTypeToStringOfLength12 (expenses[i].getAmount());
            amountOfExpensesFromTheSelectedPeriod += expenses[i].getAmount();
            cout << "|" << expenses[i].getDate() << " |" << amountInStringNotation << " |" << "   PLN   |" << expenses[i].getItem() << endl;
        }
    }
    return amountOfExpensesFromTheSelectedPeriod;
}


void CashFlowManager::showTheBalanceSheetOfTheSelectedPeriod() {
    Date startDate;
    Date endDate;
    Date currentDateInNumberFormat = getDateFromTheSystem();

    cout << "Start date - ";
    startDate = splitTheDateFromTheStringIntoIndividualElements(enterTheNewDate(currentDateInNumberFormat) + "-");

    cout << "End date - ";
    endDate = splitTheDateFromTheStringIntoIndividualElements(enterTheNewDate(currentDateInNumberFormat) + "-");

    float sumOfIncomes = calculateTheSumOfIncomesForTheSelectedPeriod(startDate, endDate);
    float sumOfExpenses = calculateTheSumOfExpensesForTheSelectedPeriod(startDate, endDate);

    showTheTotalAmountOfCashFlows (sumOfIncomes, sumOfExpenses);
}







