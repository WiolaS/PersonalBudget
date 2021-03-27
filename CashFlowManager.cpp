#include "CashFlowManager.h"
#include "AuxiliaryMethods.h"
#include <iomanip>      // setprecision

using namespace std;

Date CashFlowManager::getDateFromTheSystem() {
    return dateManager.getDateFromTheSystem();
}

Date CashFlowManager::splitTheDateFromTheStringIntoIndividualElements(string dateEnteredByTheUser) {
    return dateManager.splitTheDateFromTheStringIntoIndividualElements(dateEnteredByTheUser);
}

string CashFlowManager::enterTheNewDate(Date currentDate) {
    return dateManager.enterTheNewDate(currentDate);
}

string CashFlowManager::setTheDateOfTheCashFlow(string typeOfCashFlow) {
    return dateManager.setTheDateOfTheCashFlow(typeOfCashFlow);
}

string CashFlowManager::enterTheItemOfCashFlow() {
    string itemDescribingTheCashFlow;

    cout << "Enter an item describing the cash flow: ";
    itemDescribingTheCashFlow = AuxiliaryMethods::loadLine();

    return itemDescribingTheCashFlow;
}

float CashFlowManager::enterTheAmountOfCashFlow() {
    string enteredAmountInStringFormat;
    string decimalAmountSeparatedByADot;
    string correctedAmountToTwoDecimalPlaces;
    float amountOfCashFlowInNumberFormat;

    cout << "Enter the cash flow amount: ";
    enteredAmountInStringFormat = AuxiliaryMethods::loadLine();
    if (enteredAmountInStringFormat == "") {
        decimalAmountSeparatedByADot = "0";
    } else {
        decimalAmountSeparatedByADot = AuxiliaryMethods::checkIfThereIsAComma(enteredAmountInStringFormat);
    }
    amountOfCashFlowInNumberFormat = atof(decimalAmountSeparatedByADot.c_str());
    correctedAmountToTwoDecimalPlaces = AuxiliaryMethods::convertFloatToStringAndSetPrecisionToTwoDecimalPlaces(amountOfCashFlowInNumberFormat);
    amountOfCashFlowInNumberFormat = atof(correctedAmountToTwoDecimalPlaces.c_str());

    return amountOfCashFlowInNumberFormat;
}

CashFlow CashFlowManager::addCashFlow(string typeOfCashFlow) {
    CashFlow cashFlow;

    cashFlow.setCashFlowId(1);
    cashFlow.setUserId(LOGGED_IN_USER_ID);
    cashFlow.setDate(setTheDateOfTheCashFlow(typeOfCashFlow));
    cashFlow.setItem(enterTheItemOfCashFlow());
    cashFlow.setAmount(enterTheAmountOfCashFlow());

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

int CashFlowManager::addExpense () {
    CashFlow expense;
    string typeOfCashFlow = "expense";

    system("cls");
    expense = addCashFlow(typeOfCashFlow);
    expenses.push_back(expense);
    expenseFile.addExpenseToFile(expense);
}

void CashFlowManager::sortIncomesByDate() {
    CashFlow temp;
    Date date1;
    Date date2;

    for (int i = 0; i < incomes.size() -1; i++) {
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

void CashFlowManager::sortExpensesByDate() {
    CashFlow temp;
    Date date1;
    Date date2;

    for (int i = 0; i < expenses.size() -1; i++) {
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

bool CashFlowManager::checkIfThisCashFlowBelongsToTheLoggedInUser (int userID) {
    if (userID == LOGGED_IN_USER_ID)
        return true;
    else
        return false;
}


void CashFlowManager::showTheTotalAmountOfCashFlows (float sumOfIncomes, float sumOfExpenses) {
    float amountOfTheDifferenceBetweenIncomeAndExpense;
    string sumOfIncomesInStringFormat = "";
    string sumOfExpensesInStringFormat = "";
    string balance = "";

    amountOfTheDifferenceBetweenIncomeAndExpense = sumOfIncomes - sumOfExpenses;
    sumOfIncomesInStringFormat = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (sumOfIncomes);
    sumOfExpensesInStringFormat = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (sumOfExpenses);
    balance = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (amountOfTheDifferenceBetweenIncomeAndExpense);

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Total amount of incomes:  " << fixed <<setprecision(2) << sumOfIncomesInStringFormat << " PLN" << endl;
    cout << "Total amount of expenses: " << fixed <<setprecision(2) << sumOfExpensesInStringFormat << " PLN" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Balance:                  " << balance  << " PLN" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

float CashFlowManager::calculateTheSumOfIncomesForTheCurrentMonth() {
    Date dateInDateFormat;
    Date currentDate = getDateFromTheSystem();
    float amountOfIncomesFromTheCurrentMonth = 0;
    string amountInStringFormat = "";
    string typeOfcashFlow = "Incomes";

    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);
    if (incomes.size() > 0) {
        sortIncomesByDate();
        for (int i = 0; i < incomes.size(); i++) {
            if (checkIfThisCashFlowBelongsToTheLoggedInUser (incomes[i].getUserId())) {
                dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");
                if (currentDate.getYear() == dateInDateFormat.getYear() && currentDate.getMonth() == dateInDateFormat.getMonth() )  {

                    amountInStringFormat = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (incomes[i].getAmount());
                    amountOfIncomesFromTheCurrentMonth += incomes[i].getAmount();
                    cout << "|" << incomes[i].getDate() << " |" << amountInStringFormat << " |" << "   PLN   |" << incomes[i].getItem() << endl;
                }
            }
        }
    }
    return amountOfIncomesFromTheCurrentMonth;
}

float CashFlowManager::calculateTheSumOfExpensesForTheCurrentMonth() {
    Date dateInDateFormat;
    Date currentDate = getDateFromTheSystem();
    float amountOfExpensesFromTheCurrentMonth = 0;
    string amountInStringFormat = "";
    string typeOfcashFlow = "Expenses";

    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);
    if (expenses.size() > 0) {
        sortExpensesByDate();
        for (int i = 0; i < expenses.size(); i++) {
            if (checkIfThisCashFlowBelongsToTheLoggedInUser (expenses[i].getUserId())) {
                dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
                if (currentDate.getYear() == dateInDateFormat.getYear() && currentDate.getMonth() == dateInDateFormat.getMonth())  {

                    amountInStringFormat = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (expenses[i].getAmount());
                    amountOfExpensesFromTheCurrentMonth += expenses[i].getAmount();
                    cout << "|" << expenses[i].getDate() << " |" << amountInStringFormat << " |" << "   PLN   |" << expenses[i].getItem() << endl;
                }
            }
        }
    }
    return amountOfExpensesFromTheCurrentMonth;
}


void CashFlowManager::showTheBalanceSheetOfTheCurrentMonth() {
    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "            >>> 3. Balance sheet from the current month  <<<        " << endl;
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
    string amountInStringFormat = "";
    string typeOfcashFlow = "Incomes";

    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);
    if (incomes.size() > 0) {
        sortIncomesByDate();
        for (int i = 0; i < incomes.size(); i++) {
            if (checkIfThisCashFlowBelongsToTheLoggedInUser (incomes[i].getUserId())) {
                dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");

                if ((currentDate.getYear() == dateInDateFormat.getYear() && currentDate.getMonth() == (dateInDateFormat.getMonth() + 1)) ||
                        (currentDate.getYear() == (dateInDateFormat.getYear() + 1) && (currentDate.getMonth() == numberOfTheFirstMonthOfTheYear &&
                                dateInDateFormat.getMonth() == numberOfTheLasttMonthOfTheYear)))  {

                    amountInStringFormat = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (incomes[i].getAmount());
                    amountOfIncomesFromThePreviousMonth += incomes[i].getAmount();
                    cout << "|" << incomes[i].getDate() << " |" << amountInStringFormat << " |" << "   PLN   |" << incomes[i].getItem() << endl;
                }
            }
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
    string amountInStringFormat = "";
    string typeOfcashFlow = "Expenses";

    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);
    if (expenses.size() > 0) {
        sortExpensesByDate();
        for (int i = 0; i < expenses.size(); i++) {
            if (checkIfThisCashFlowBelongsToTheLoggedInUser (expenses[i].getUserId())) {
                dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
                if ((currentDate.getYear() == dateInDateFormat.getYear() && currentDate.getMonth() == (dateInDateFormat.getMonth() + 1)) ||
                        (currentDate.getYear() == (dateInDateFormat.getYear() + 1) && (currentDate.getMonth() == numberOfTheFirstMonthOfTheYear &&
                                dateInDateFormat.getMonth() == numberOfTheLasttMonthOfTheYear)))  {

                    amountInStringFormat = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (expenses[i].getAmount());
                    amountOfExpensesFromThePreviousMonth += expenses[i].getAmount();
                    cout << "|" << expenses[i].getDate() << " |" << amountInStringFormat << " |" << "   PLN   |" << expenses[i].getItem() << endl;
                }
            }
        }
    }
    return amountOfExpensesFromThePreviousMonth;
}

void CashFlowManager::showTheBalanceSheetOfThePrevoiusMonth() {
    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "            >>> 4. Balance sheet from the previous month <<<        " << endl;
    float sumOfIncomes = calculateTheSumOfIncomesForThePreviousMonth();
    float sumOfExpenses = calculateTheSumOfExpensesForThePreviousMonth();

    showTheTotalAmountOfCashFlows (sumOfIncomes, sumOfExpenses);
}

float CashFlowManager::calculateTheSumOfIncomesForTheSelectedPeriod(Date startDate, Date endDate) {
    Date dateInDateFormat;
    Date currentDateInNumberFormat = getDateFromTheSystem();
    float amountOfIncomesFromTheSelectedPeriod = 0;
    string amountInStringFormat = "";
    string typeOfcashFlow = "Incomes";

    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);
    if (incomes.size() > 0) {
        sortIncomesByDate();
        for (int i = 0; i < incomes.size(); i++) {
            if (checkIfThisCashFlowBelongsToTheLoggedInUser (incomes[i].getUserId())) {
                dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(incomes[i].getDate() + "-");

                if ((startDate.getYear() < dateInDateFormat.getYear() ||
                        startDate.getYear() == dateInDateFormat.getYear() && startDate.getMonth() < dateInDateFormat.getMonth() ||
                        startDate.getYear() == dateInDateFormat.getYear() && startDate.getMonth() == dateInDateFormat.getMonth() && startDate.getDay() <= dateInDateFormat.getDay()) &&

                        (endDate.getYear() > dateInDateFormat.getYear() ||
                         endDate.getYear() == dateInDateFormat.getYear() && endDate.getMonth() > dateInDateFormat.getMonth() ||
                         endDate.getYear() == dateInDateFormat.getYear() && endDate.getMonth() == dateInDateFormat.getMonth() && endDate.getDay() >= dateInDateFormat.getDay())) {

                    amountInStringFormat = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (incomes[i].getAmount());
                    amountOfIncomesFromTheSelectedPeriod += incomes[i].getAmount();
                    cout << "|" << incomes[i].getDate() << " |" << amountInStringFormat << " |" << "   PLN   |" << incomes[i].getItem() << endl;
                }
            }
        }
    }
    return amountOfIncomesFromTheSelectedPeriod;
}

float CashFlowManager::calculateTheSumOfExpensesForTheSelectedPeriod(Date startDate, Date endDate) {
    Date dateInDateFormat;
    float amountOfExpensesFromTheSelectedPeriod = 0;
    string amountInStringFormat = "";
    string typeOfcashFlow = "Expenses";

    AuxiliaryMethods::layoutShowingTheSelectedCashFlow (typeOfcashFlow);
    if (expenses.size() > 0) {
        sortExpensesByDate();
        for (int i = 0; i < expenses.size(); i++) {
            if (checkIfThisCashFlowBelongsToTheLoggedInUser (expenses[i].getUserId())) {
                dateInDateFormat = splitTheDateFromTheStringIntoIndividualElements(expenses[i].getDate() + "-");
                if ((startDate.getYear() < dateInDateFormat.getYear() ||
                        startDate.getYear() == dateInDateFormat.getYear() && startDate.getMonth() < dateInDateFormat.getMonth() ||
                        startDate.getYear() == dateInDateFormat.getYear() && startDate.getMonth() == dateInDateFormat.getMonth() && startDate.getDay() <= dateInDateFormat.getDay()) &&

                        (endDate.getYear() > dateInDateFormat.getYear() ||
                         endDate.getYear() == dateInDateFormat.getYear() && endDate.getMonth() > dateInDateFormat.getMonth() ||
                         endDate.getYear() == dateInDateFormat.getYear() && endDate.getMonth() == dateInDateFormat.getMonth() && endDate.getDay() >= dateInDateFormat.getDay())) {

                    amountInStringFormat = AuxiliaryMethods::changeTheFloatTypeToStringOfLength12 (expenses[i].getAmount());
                    amountOfExpensesFromTheSelectedPeriod += expenses[i].getAmount();
                    cout << "|" << expenses[i].getDate() << " |" << amountInStringFormat << " |" << "   PLN   |" << expenses[i].getItem() << endl;
                }
            }
        }
    }
    return amountOfExpensesFromTheSelectedPeriod;
}

void CashFlowManager::showTheBalanceSheetOfTheSelectedPeriod() {
    Date startDate;
    Date endDate;
    Date currentDateInNumberFormat = getDateFromTheSystem();
    float sumOfIncomes;
    float sumOfExpenses;

    system("cls");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "            >>> 5. Balance sheet from the selected period <<<       " << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Start date - ";
    startDate = splitTheDateFromTheStringIntoIndividualElements(enterTheNewDate(currentDateInNumberFormat) + "-");
    cout << "End date - ";
    endDate = splitTheDateFromTheStringIntoIndividualElements(enterTheNewDate(currentDateInNumberFormat) + "-");
    sumOfIncomes = calculateTheSumOfIncomesForTheSelectedPeriod(startDate, endDate);
    sumOfExpenses = calculateTheSumOfExpensesForTheSelectedPeriod(startDate, endDate);
    showTheTotalAmountOfCashFlows (sumOfIncomes, sumOfExpenses);
}







