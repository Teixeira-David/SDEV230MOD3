// ----------------------------------------------------------------
// Author: David Teixeira 
// Project: Unit 7 Exercise 7-5
// Course: SDEV-230
// Creation Date: 11/10/2023
// ----------------------------------------------------------------

// Import the Preprocessor Directives
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <limits>

// Provide scope to identifiers inside the standard library
using namespace std;

// Create the constants
const double dblFIRST_TIER_PERCENT = 0.15; 
const double dblSECOND_TIER_PERCENT = 0.25; 
const double dblTHIRD_TIER_PERCENT = 0.35; 
const double dblFIRST_TIER_MIN = 15000.0;
const double dblSECOND_TIER_MIN = 40000.0;
const double dblSECOND_TIER_FIXED_RATE = 2250.00;
const double dblTHIRD_TIER_FIXED_RATE = 8460.00;
const double dblSINGLE_STANDARD_EXEMPTION_RATE = 4000.00;
const double dblMARRIED_EXEMPTION_RATE = 7000.00;
const double dblEXEMPTION_RATE_PER_PERSON = 1500.00;

// Place the headers for each function
void getData();
char Get_Marital_Status();
int Get_Dependent_Count();
double Get_Gross_Income();
double taxAmount(double& dblGrossIncomeInput, string& strMaritalStatus, int& intDependentCount, double& dblPensionPercent); 
double Get_Pension_Percent();
double Calc_Total_Pension_Saved(double& dblGrossIncomeResult, double& dblPensionPercent);
double Calc_Total_Tax_Withdrawal();
// void Display_Results(double& dblGrossIncomeInput, double& dblGrossIncomeResult, double& dblTaxAmountResult, 
//                     double& dblPensionPercent, double& dblPensionTotal, string& strMaritalStatus, int& intDependentCount);

int main() 
{
    // Get the user inputs
    getData();
    
    // Main should return an int   
    return 0;  
}    

void getData() 
/*
Function Name: getData
Function Purpose: Function is to get the inputs from the user.
*/
{
    // Create the Local Variables
    double dblGrossIncomeInput, dblTaxAmountResult, dblPensionPercent;
    char chrMaritalStatus;
    int intDependentCount;
    string astrMaritalStatus[] = {"Single", "Married"};
    string strMaritalStatus;

    // Get the input of the marital status
    chrMaritalStatus = Get_Marital_Status();

    // Check if the marital status is married or single. If married, get the dependent count
    if (chrMaritalStatus == 'm' || chrMaritalStatus == 'M') {
        strMaritalStatus = astrMaritalStatus[1];
        intDependentCount = Get_Dependent_Count(); 

        // Get the total income for both spouses
        dblGrossIncomeInput = Get_Gross_Income();

    } else {
        intDependentCount = 0;
        strMaritalStatus = astrMaritalStatus[0];
        // Get the gross income from the user
        dblGrossIncomeInput = Get_Gross_Income();
    }

    // Get the pension percentage and calculate the total saved
    dblPensionPercent = Get_Pension_Percent();

    // Get the tax amount 
    dblTaxAmountResult = taxAmount(dblGrossIncomeInput, strMaritalStatus, intDependentCount, dblPensionPercent);
    
    // Display the result
    cout << "Federal tax owed: $" << dblTaxAmountResult << endl;

}

char Get_Marital_Status()
/*
Function Name: Get_Marital_Status
Function Purpose: Function is to get the marital status from the user.
*/
{
    // Declare Local Variables
    char chrInput;

    // Get the user input for marital status
    cout << "Please enter 's or S' for Single Status, or 'm or M' for Married Status: ";
    while (true) {
        // First check if the user has entered the desired input
        if (!(cin >> chrInput)) {
            // Display error message to user about the incorrect input
            cout << "Invalid input. Input must be 's or S' or 'm or M'. Please try again." << endl;
            // Clear the error flag and ignore the rest of the line
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (chrInput == 's' || chrInput == 'S') {
            // The user has declared they are single status
            return chrInput;
        } else if (chrInput == 'm' || chrInput == 'M') {
            // The user has declared they are married status
            return chrInput;
        } else {
            cout << "Invalid input. Input must be 's or S' or 'm or M'. Please try again." << endl;
        }
    }
}  

int Get_Dependent_Count()
/*
Function Name: Get_Dependent_Count
Function Purpose: Function is to get the dependant count if the user has declared they are married status.
*/
{
    // Declare Local Variables
    int intDependInput = 0;

    // Get the user input for if they have dependents under the age of 14 years old
    cout << "Please enter the number of dependents in your house hold: ";
    while (true) {
        // First check if the user has entered the desired input
        if (!(cin >> intDependInput)) {
            // Display error message to user about the incorrect input
            cout << "Invalid input. Input must be an integer. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (intDependInput >= 0) {
            return intDependInput;
        } else {
            cout << "Invalid input. Input must be a positive integer. Please try again.";
            cin.clear();
        }
    }
}

double Get_Gross_Income()
/*
Function Name: Get_Gross_Income
Function Purpose: Function is to gets the gross income from the user.
*/
{
    // Declare Local Variables
    double dblIncomeInput;

    // Set the decimal precision
    cout << fixed << setprecision(2);

    // Get the input for the dependents
    cout << "Please enter the gross income: $";
    while (true) {
        // First check if the user has entered the desired input
        if (!(cin >> dblIncomeInput)) {
            // Display error message to user about the incorrect input
            cout << "Invalid input. Input must be a double. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (dblIncomeInput >= 0) {
            return dblIncomeInput;
        } else {
            cout << "Invalid input. Input must be a positive double. Please try again.";
            cin.clear();
        }
    }
}

double taxAmount(double& dblGrossIncomeInput, string& strMaritalStatus, int& intDependentCount, double& dblPensionPercent)
/*
Function Name: taxAmount
Function Purpose: Function is to calculate the tax amount based off the user input.
*/
{
    // Declare Local Variables
    double dblExemptionAmount;
    double dblTaxIncome;

    // Get the exemption amount
    if (strMaritalStatus == "Married") {
        dblExemptionAmount = dblMARRIED_EXEMPTION_RATE + (dblEXEMPTION_RATE_PER_PERSON * (intDependentCount + 2));
    } else {
        dblExemptionAmount = dblSINGLE_STANDARD_EXEMPTION_RATE + dblEXEMPTION_RATE_PER_PERSON;
    }

    // Calculate the taxable income amount
    dblTaxIncome = dblGrossIncomeInput - dblExemptionAmount - (dblGrossIncomeInput * dblPensionPercent); 
    if (dblTaxIncome <= dblFIRST_TIER_MIN) {
        return dblTaxIncome * dblFIRST_TIER_PERCENT;
    } else if (dblTaxIncome <= dblSECOND_TIER_MIN) {
        return dblSECOND_TIER_FIXED_RATE + (dblTaxIncome - dblFIRST_TIER_MIN) * dblSECOND_TIER_PERCENT;
    } else {
        return dblTHIRD_TIER_FIXED_RATE + (dblTaxIncome - dblSECOND_TIER_MIN) * dblTHIRD_TIER_PERCENT;
    }
}

double Get_Pension_Percent()
/*
Function Name: Get_Pension_Percent
Function Purpose: Function is to gets the pension percent from the user.
*/
{
    // Declare Local Variables
    double dblPensionInput = 0.0;

    // Set the decimal precision
    cout << fixed << setprecision(2);

    // Get the input for the dependents
    cout << "Please enter the pension percentage (0-6): %";
    while (true) {
        // First check if the user has entered the desired input
        if (!(cin >> dblPensionInput)) {
            // Display error message to user about the incorrect input
            cout << "Invalid input. Input must be a double. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (dblPensionInput >= 0.0 && dblPensionInput <= 6.0) {
            return dblPensionInput / 100;
        } else {
            cout << "Invalid input. Input must be a positive double and <= 6. Please try again." << endl;
            cin.clear();
        }
    }
}

double Calc_Total_Pension_Saved(double& dblGrossIncomeInput, double& dblPensionPercent)
/*
Function Name: Calc_Total_Pension_Saved
Function Purpose: Function is to calculate the total of the pension saved.
*/
{
    // Declare Local Variables
    double dblTotalPensionResult = 0.0;

    // Set the decimal precision
    cout << fixed << setprecision(2);

    // Calculate the tax amount
    dblTotalPensionResult = dblGrossIncomeInput * dblPensionPercent;

    return dblTotalPensionResult;
}

// void Display_Results(double& dblGrossIncomeInput, double& dblGrossIncomeResult, double& dblTaxAmountResult, 
//                     double& dblPensionPercent, double& dblPensionTotal, string& strMaritalStatus, int& intDependentCount)
// /*
// Function Name: Display_Results
// Function Purpose: Function is to display the results.
// */
// {
//     cout << "----------------------------- Tax Results -----------------------------" << endl;
//     cout << setfill('.') << left << setw(40) << "Marital Status: " << right << strMaritalStatus << endl;
//     cout << setfill('.') << left << setw(40) << "Total Dependents: " << right  << intDependentCount << endl;
//     cout << setfill('.') << left << setw(40) << "Total Pension Percentage: " << right << fixed << setprecision(2) << "%" << dblPensionPercent << endl;
//     cout << setfill('.') << left << setw(40) << "Total Pension Saved: " << right << fixed << setprecision(2) << "$" << dblPensionTotal << endl;
//     cout << setfill('.') << left << setw(40) << "Total Gross Income Before Tax: " << right << "$"  << dblGrossIncomeInput << endl;
//     cout << setfill('.') << left << setw(40) << "Total Tax On Gross Income: " << right << "$"  << dblTaxAmountResult << endl;
//     cout << setfill('.') << left << setw(40) << "Total Gross Income After Tax: " << right << fixed << setprecision(2) << "$" << dblGrossIncomeResult << endl;
//     cout << endl;
// }