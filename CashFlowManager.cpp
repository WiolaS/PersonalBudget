#include "CashFlowManager.h"
#include "AuxiliaryMethods.h"

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

    cout << endl << "Please enter date in the format yyyy-mm-dd." << endl;
    cout << "Please also note that the date should be in the range of" << endl;
    cout << "2000-01-01 to the last day of the current month: ";

    dateEnteredByTheUser = AuxiliaryMethods::loadLine();
    dateEnteredByTheUserInNumberFormat = splitTheDateFromTheStringIntoIndividualElements(dateEnteredByTheUser + "-");

    if (checkTheCorrectnesOfTheEnteredDate(dateEnteredByTheUserInNumberFormat, currentDate) == true)
        return dateEnteredByTheUser;
    else
        dateEnteredByTheUser = enterTheNewDate (currentDate);
}

string CashFlowManager::setTheDateOfTheCashFlow () {

    string dateEnteredByTheUser;
    Date currentDateInNumberFormat;
    string dateOfTheCashFlow;
    char choice;
    CashFlow cashFlow;

    currentDateInNumberFormat = getDateFromTheSystem ();
    choice = AuxiliaryMethods::selectAnOptionFromTheCashFlowMenu();

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

CashFlow CashFlowManager::addCashFlow() {
    CashFlow cashFlow;

    cashFlow.setCashFlowId(1); // to change
    cashFlow.setUserId(LOGGED_IN_USER_ID);
    cashFlow.setDate(setTheDateOfTheCashFlow());
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
    system("cls");
    cout << " >>> ADD NEW INCOME <<<" << endl << endl;
    system("pause");
    income = addCashFlow();

    incomes.push_back(income);
    incomeFile.addIncomeToFile(income);

}


int CashFlowManager::addExpense () {

    CashFlow expense;
    system("cls");
    cout << " >>> ADD NEW EXPENSE <<<" << endl << endl;
    system("pause");
    expense = addCashFlow();

    expenses.push_back(expense);
    expenseFile.addExpenseToFile(expense);

}


float CashFlowManager::calculateTheSumOfIncomesForThePreviousMonth() {
    cout << "Test 1" << endl;
    Date selectedIncomeDates;
    Date currentDate = getDateFromTheSystem ();
    int numberOfTheFirstMonthOfTheYear = 1;
    int numberOfTheLasttMonthOfTheYear = 12;
    float amountOfIncomesFromThePreviousMonth = 0;

    for (int i = 0; i < incomes.size(); i++) {
        cout << "Test 2" << endl;
        //cashFlowDates[i] = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");
        selectedIncomeDates = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");

        cout << "Test 3" << endl;

        if ((currentDate.getYear() == selectedIncomeDates.getYear() && currentDate.getMonth() == (selectedIncomeDates.getMonth() + 1)) ||
                (currentDate.getYear() == (selectedIncomeDates.getYear() + 1) && (currentDate.getMonth() == numberOfTheFirstMonthOfTheYear &&
                        selectedIncomeDates.getMonth() == numberOfTheLasttMonthOfTheYear)))  {

            cout << "Test 4" << endl;
            amountOfIncomesFromThePreviousMonth += incomes[i].getAmount();

        }
    }
    cout << "Test 5" << endl;
    cout << "amountOfIncomesFromThePreviousMonth" << amountOfIncomesFromThePreviousMonth << endl;
    system("pause");

    return amountOfIncomesFromThePreviousMonth;
}

float CashFlowManager::calculateTheSumOfExpensesForThePreviousMonth() {
    Date selectedExpensesDates;
    Date currentDate = getDateFromTheSystem();
    int numberOfTheFirstMonthOfTheYear = 1;
    int numberOfTheLasttMonthOfTheYear = 12;
    float amountOfExpensesFromThePreviousMonth = 0;

    for (int i = 0; i < expenses.size(); i++) {
        selectedExpensesDates = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
        if ((currentDate.getYear() == selectedExpensesDates.getYear() && currentDate.getMonth() == (selectedExpensesDates.getMonth() + 1)) ||
                (currentDate.getYear() == (selectedExpensesDates.getYear() + 1) && (currentDate.getMonth() == numberOfTheFirstMonthOfTheYear &&
                        selectedExpensesDates.getMonth() == numberOfTheLasttMonthOfTheYear)))  {
            amountOfExpensesFromThePreviousMonth += expenses[i].getAmount();
        }
    }
    return amountOfExpensesFromThePreviousMonth;
}

float CashFlowManager::calculateTheSumOfIncomesForTheCurrentMonth() {
    // system("cls");
    cout << "----------------------------------------------" << endl;
    cout << "--Income--------------------------------------" << endl;
    Date selectedIncomesDates;
    Date currentDate = getDateFromTheSystem();
    float amountOfIncomesFromTheCurrentMonth = 0;

    for (int i = 0; i < incomes.size(); i++) {
        selectedIncomesDates = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");
        if (currentDate.getYear() == selectedIncomesDates.getYear() && currentDate.getMonth() == selectedIncomesDates.getMonth() )  {
            amountOfIncomesFromTheCurrentMonth += incomes[i].getAmount();
            cout << "----------------------------------------------" << endl;
            cout << "--Income--------------------------------------" << endl;
            cout << "Date:      " << incomes[i].getDate() << endl;
            cout << "Item:      " << incomes[i].getItem() << endl;
            cout << "Amount:    " << incomes[i].getAmount() << endl;

        }
    }
    return amountOfIncomesFromTheCurrentMonth;
}

float CashFlowManager::calculateTheSumOfExpensesForTheCurrentMonth() {
    Date selectedExpensesDates;
    Date currentDate = getDateFromTheSystem();
    float amountOfExpensesFromTheCurrentMonth = 0;

    for (int i = 0; i < expenses.size(); i++) {
        selectedExpensesDates = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
        if (currentDate.getYear() == selectedExpensesDates.getYear() && currentDate.getMonth() == selectedExpensesDates.getMonth())  {
            amountOfExpensesFromTheCurrentMonth += expenses[i].getAmount();
            cout << "----------------------------------------------" << endl;
            cout << "--Expenses------------------------------------" << endl;
            cout << "Date:      " << expenses[i].getDate() << endl;
            cout << "Item:      " << expenses[i].getItem() << endl;
            cout << "Amount:    " << expenses[i].getAmount() << endl;
        }
    }
    return amountOfExpensesFromTheCurrentMonth;
}

float CashFlowManager::calculateTheSumOfIncomesForTheSelectedPeriod() {
    cout << "Test 1" << endl;

    Date startDate;
    Date endDate;
    Date selectedIncomeDates;
    Date currentDateInNumberFormat = getDateFromTheSystem();
    float amountOfIncomesFromTheSelectedPeriod = 0;

    cout << "Start date: " <<endl;
    startDate = splitTheDateFromTheStringIntoIndividualElements(enterTheNewDate(currentDateInNumberFormat) + "-");

    cout << "End date: " <<endl;
    endDate = splitTheDateFromTheStringIntoIndividualElements(enterTheNewDate(currentDateInNumberFormat) + "-");

    for (int i = 0; i < incomes.size(); i++) {
        cout << "Test 2" << endl;
        selectedIncomeDates = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");

        cout << "Test 3" << endl;
        if ((startDate.getYear() <= selectedIncomeDates.getYear() && startDate.getMonth() <= selectedIncomeDates.getMonth() && startDate.getDay() <= selectedIncomeDates.getDay()) &&
                (endDate.getYear() >= selectedIncomeDates.getYear() && endDate.getMonth() >= selectedIncomeDates.getMonth() && endDate.getDay() >= selectedIncomeDates.getDay())) {

            cout << "Test 4" << endl;
            amountOfIncomesFromTheSelectedPeriod += incomes[i].getAmount();
        }
    }
    cout << "Test 5" << endl;
    cout << "amountOfIncomesFromThePreviousMonth" << amountOfIncomesFromTheSelectedPeriod << endl;
    system("pause");

    return amountOfIncomesFromTheSelectedPeriod;
}


float CashFlowManager::calculateTheSumOfExpensesForTheSelectedPeriod(Date startDate, Date endDate) {

    Date selectedExpensesDates;
    float amountOfExpensesFromTheSelectedPeriod = 0;

    for (int i = 0; i < incomes.size(); i++) {
        selectedExpensesDates = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");
        if ((startDate.getYear() <= selectedExpensesDates.getYear() && startDate.getMonth() <= selectedExpensesDates.getMonth() && startDate.getDay() <= selectedExpensesDates.getDay()) &&
                (endDate.getYear() >= selectedExpensesDates.getYear() && endDate.getMonth() >= selectedExpensesDates.getMonth() && endDate.getDay() >= selectedExpensesDates.getDay())) {
            amountOfExpensesFromTheSelectedPeriod += incomes[i].getAmount();
        }
    }
    cout << "amountOfIncomesFromThePreviousMonth" << amountOfExpensesFromTheSelectedPeriod << endl;
    system("pause");

    return amountOfExpensesFromTheSelectedPeriod;
}


void CashFlowManager::showTheBalanceSheetOfTheSelectedPeriod() {
    Date startDate;
    Date endDate;
    Date currentDateInNumberFormat = getDateFromTheSystem();

    cout << "Start date: " <<endl;
    startDate = splitTheDateFromTheStringIntoIndividualElements(enterTheNewDate(currentDateInNumberFormat) + "-");

    cout << "End date: " <<endl;
    endDate = splitTheDateFromTheStringIntoIndividualElements(enterTheNewDate(currentDateInNumberFormat) + "-");

    float sumOfIncomes = calculateTheSumOfIncomesForTheSelectedPeriod();
    float sumOfExpenses = calculateTheSumOfExpensesForTheSelectedPeriod(startDate, endDate);
    float amountOfTheDifferenceBetweenIncomeAndExpense;

    if (sumOfIncomes >= sumOfExpenses) {
        amountOfTheDifferenceBetweenIncomeAndExpense = sumOfIncomes - sumOfExpenses;
    } else
        amountOfTheDifferenceBetweenIncomeAndExpense = sumOfExpenses - sumOfIncomes;

    cout << "----------------------------------------------" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Total amount of incomes: " << sumOfIncomes << endl;
    cout << "Total amount of expenses: " << sumOfExpenses << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Balance: " << amountOfTheDifferenceBetweenIncomeAndExpense << endl;
    system("pause");
}



float CashFlowManager::showTheBalanceSheetOfThePrevoiusMonth() {
    float sumOfIncomes = calculateTheSumOfIncomesForThePreviousMonth();
    float sumOfExpenses = calculateTheSumOfExpensesForThePreviousMonth();
    float amountOfTheDifferenceBetweenIncomeAndExpense;

    if (sumOfIncomes >= sumOfExpenses) {
        amountOfTheDifferenceBetweenIncomeAndExpense = sumOfIncomes - sumOfExpenses;
    } else
        amountOfTheDifferenceBetweenIncomeAndExpense = sumOfExpenses - sumOfIncomes;

    cout << "amountOfTheDifferenceBetweenIncomeAndExpense" << amountOfTheDifferenceBetweenIncomeAndExpense << endl;
    system("pause");
    return amountOfTheDifferenceBetweenIncomeAndExpense;
}

void CashFlowManager::showTheBalanceSheetOfTheCurrentMonth() {
    float sumOfIncomes = calculateTheSumOfIncomesForTheCurrentMonth();
    float sumOfExpenses = calculateTheSumOfExpensesForTheCurrentMonth();
    float amountOfTheDifferenceBetweenIncomeAndExpense;

    if (sumOfIncomes >= sumOfExpenses) {
        amountOfTheDifferenceBetweenIncomeAndExpense = sumOfIncomes - sumOfExpenses;
    } else
        amountOfTheDifferenceBetweenIncomeAndExpense = sumOfExpenses - sumOfIncomes;

    cout << "----------------------------------------------" << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Total amount of incomes: " << sumOfIncomes << endl;
    cout << "Total amount of expenses: " << sumOfExpenses << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Balance: " << amountOfTheDifferenceBetweenIncomeAndExpense << endl;
    system("pause");
}




/*
    cout << "Test 1" << endl;

    float amountOfIncomesFromThePreviousMonth;
    float amountOfExpensesFromThePreviousMonth;
    float differenceBetweenIncomeAndExpense;
    int numberOfTheFirstMonthOfTheYear = 1;
    int numberOfTheLasttMonthOfTheYear = 12;
    vector <Date> cashFlowDates; // to remove
    Date currentDate = getDateFromTheSystem ();
    Date testDate;

    cout << "Test 2" << endl;

    for (int i = 0; i < incomes.size(); i++) {
        cout << "Test 3" << endl;
        //cashFlowDates[i] = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");
        selectedIncomeDates = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");

        cout << "Test 4" << endl;

        if ((currentDate.getYear() == cashFlowDates[i].getYear() && currentDate.getMonth() == (cashFlowDates[i].getMonth() + 1)) ||
                (currentDate.getYear() == (cashFlowDates[i].getYear() + 1) && (currentDate.getMonth() == numberOfTheFirstMonthOfTheYear &&
                        cashFlowDates[i].getMonth() == numberOfTheLasttMonthOfTheYear)))  {

            cout << "Test 5" << endl;

            amountOfIncomesFromThePreviousMonth += incomes[i].getAmount();


        }
    }
    cout << "amountOfIncomesFromThePreviousMonth" << amountOfIncomesFromThePreviousMonth << endl;
    cout << "amountOfExpensesFromThePreviousMonth" << amountOfExpensesFromThePreviousMonth << endl;

    differenceBetweenIncomeAndExpense = calcutateTheDifferenceBetweenIncomeAndExpense(amountOfIncomesFromThePreviousMonth, amountOfExpensesFromThePreviousMonth);
    cout << "differenceBetweenIncomeAndExpense" << differenceBetweenIncomeAndExpense << endl;


    return differenceBetweenIncomeAndExpense;
}




float CashFlowManager::showTheBalanceSheetOfThePrevoiusMonth() {

    cout << "Test 1" << endl;

    float amountOfIncomesFromThePreviousMonth;
    float amountOfExpensesFromThePreviousMonth;
    float differenceBetweenIncomeAndExpense;
    int numberOfTheFirstMonthOfTheYear = 1;
    int numberOfTheLasttMonthOfTheYear = 12;
    vector <Date> cashFlowDates; // to remove
    Date currentDate = getDateFromTheSystem ();
    Date testDate;

    cout << "Test 2" << endl;

    for (int i = 0; i < incomes.size(); i++) {
        cout << "Test 3" << endl;
        //cashFlowDates[i] = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");
        selectedIncomeDates = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");

        cout << "Test 4" << endl;

        if ((currentDate.getYear() == cashFlowDates[i].getYear() && currentDate.getMonth() == (cashFlowDates[i].getMonth() + 1)) ||
                (currentDate.getYear() == (cashFlowDates[i].getYear() + 1) && (currentDate.getMonth() == numberOfTheFirstMonthOfTheYear &&
                        cashFlowDates[i].getMonth() == numberOfTheLasttMonthOfTheYear)))  {

            cout << "Test 5" << endl;

            amountOfIncomesFromThePreviousMonth += incomes[i].getAmount();


        }
    }
    cout << "amountOfIncomesFromThePreviousMonth" << amountOfIncomesFromThePreviousMonth << endl;
    cout << "amountOfExpensesFromThePreviousMonth" << amountOfExpensesFromThePreviousMonth << endl;

    differenceBetweenIncomeAndExpense = calcutateTheDifferenceBetweenIncomeAndExpense(amountOfIncomesFromThePreviousMonth, amountOfExpensesFromThePreviousMonth);
    cout << "differenceBetweenIncomeAndExpense" << differenceBetweenIncomeAndExpense << endl;


    return differenceBetweenIncomeAndExpense;
}

*/



/*
void CashFlowManager::selectCashFlowFromThePreviousMonth (Date dateFromTheSystem) {

    CashFlow cashFlowFromThePreviousMonth;
    vector <Date> selectedDates; // to remove

    for (int i = 0; i < testDates.size(); i++) {
        if ((dateFromTheSystem.year == testDates[i].year && dateFromTheSystem.month == (testDates[i].month + 1)) ||
                (dateFromTheSystem.year == (testDates[i].year + 1) && (dateFromTheSystem.month == 1 && testDates[i].month == 12)))  {

            selectedDates.push_back(testDates[i]);
        }
    }

}

/*
void showDatesForThePreviousMonth (Date dateFromTheSystem, vector <Date> testDates) {
    vector <Date> selectedDates;

    for (int i = 0; i < testDates.size(); i++) {
        if ((dateFromTheSystem.year == testDates[i].year && dateFromTheSystem.month == (testDates[i].month + 1)) ||
                (dateFromTheSystem.year == (testDates[i].year + 1) && (dateFromTheSystem.month == 1 && testDates[i].month == 12)))  {

            selectedDates.push_back(testDates[i]);
        }
    }
    cout << endl << "// show dates for the previous month: " << endl;
     for (int i = 0; i < selectedDates.size(); i++) {
        cout << "   selectedDates[i] = " << i << "]: " << selectedDates[i].year << "-" << selectedDates[i].month << "-" << selectedDates[i].day << endl;
    }
}
*/

