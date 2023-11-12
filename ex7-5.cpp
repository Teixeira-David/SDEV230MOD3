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
const double dblFIRST_TIER_PERCENT = 0.15; // This is the first percentage of range 0-15,000
const double dblSECOND_TIER_PERCENT = 0.25; // This is the second percentage of range 15,001-40,000
const double dblTHIRD_TIER_PERCENT = 0.35; // This is the third percentage of range >= 40,001
const double dblFIRST_TIER_MIN = 15000.0;
const double dblSECOND_TIER_MIN = 40000.0;
const double dblSECOND_TIER_FIXED_RATE = 2250.00;
const double dblTHIRD_TIER_FIXED_RATE = 8460.00;
const int intSPOUSE_COUNT = 2;

// Place the headers for each function
void getData();
bool Sentinel_Control();
char Get_Marital_Status();
int Get_Dependent_Count();
double Get_Gross_Income();
double taxAmount(double& dblGrossIncomeInput); 
double Get_Pension_Percent();
double Calc_Total_Pension_Saved(double& dblGrossIncomeResult, double& dblPensionPercent);
double Calc_Total_Tax_Withdrawal();
void Display_Results(double& dblGrossIncomeInput, double& dblGrossIncomeResult, double& dblTaxAmountResult, 
                    double& dblPensionPercent, double& dblPensionTotal, string& strMaritalStatus, int& intDependentCount);

int main() 
{
    // Create the Local Variables
    bool blnFlag = true;

    // // Get the sentinel control value
    // blnFlag = Sentinel_Control();

    // Create the while loop until the user wants to exit the program
    while (blnFlag != false) {
        // Display instruction message to user
        cout << "----------------------------------------------------------------" << endl;
        cout << "You will be prompted to enter your marital status, gross income," << endl;
        cout << "dependant count, and pension percentage to calculate the federal tax sum." << endl;
        cout << "----------------------------------------------------------------" << endl;

        // Get the user inputs
        getData();

        // // Get the sentinel control value
        // blnFlag = Sentinel_Control();
    }
    
    // Main should return an int   
    return 0;  
}    

bool Sentinel_Control()
/*
Function Name: Sentinel_Control
Function Purpose: Function is to gets the continuation selection from the user.
*/
{
    // Declare Local Variables
    int intSentinelInput;

    // Get the user input 
    cout << "Please enter '1' to continue with the program, or '0' to exit the program: ";

    while (true) {
        // First check if the user has entered the desired input
        if (!(cin >> intSentinelInput)) {
            // Display error message to user about the incorrect input
            cout << "Invalid input. Input must be '1' or '0'. Please try again." << endl;
            // Clear the error flag and ignore the rest of the line
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (intSentinelInput == 1) {
                    return true; // Continue the program
                } else if (intSentinelInput == 0) {
                    return false; // Exit the program
                } else {
                    cout << "Invalid input. Input must be '1' or '0'. Please try again." << endl;
                }
            }
}

void getData() 
/*
Function Name: getData
Function Purpose: Function is to get the inputs from the user.
*/
{
    // Create the Local Variables
    double dblGrossIncomeInput, dblGrossIncomeResult, dblTaxAmountResult, dblPensionTotal, dblPensionPercent;
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

        // // Get the total income for both spouses
        // dblGrossIncomeInput = 0.0;
        // for (int i = 0; i < intSPOUSE_COUNT; i++) {
        //     dblGrossIncomeInput += Get_Gross_Income();
        // }
        // Didn't need to find gross income for both spouses, just the collective
        dblGrossIncomeInput += Get_Gross_Income();
        
    } else {
        intDependentCount = 0;
        strMaritalStatus = astrMaritalStatus[0];
        // Get the gross income from the user
        dblGrossIncomeInput = Get_Gross_Income();
    }

    // Get the tax amount 
    dblTaxAmountResult = taxAmount(dblGrossIncomeInput);

    // Calculate the remaining gross income total
    dblGrossIncomeResult = dblGrossIncomeInput - dblTaxAmountResult;

    // Get the pension percentage and calculate the total saved
    dblPensionPercent = Get_Pension_Percent();
    if (dblPensionPercent > 0) {
        // Calculate the pension total saved
        dblPensionTotal = Calc_Total_Pension_Saved(dblGrossIncomeResult, dblPensionPercent);
        // Since the user has saved for pension plan, subtract the pension total from the gross income 
        dblGrossIncomeResult -= dblPensionTotal;
    }
    
    // Display the result
    cout << "\n" << endl;
    Display_Results(dblGrossIncomeInput, dblGrossIncomeResult, dblTaxAmountResult, dblPensionPercent, dblPensionTotal, strMaritalStatus, intDependentCount);
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
    char chrInput;

    // Get the user input for if they have dependents under the age of 14 years old
    cout << "Please enter 'y or Y' for if you have any dependents under the age of 14, or 'n or N' for No: ";
    while (true) {
        // First check if the user has entered the desired input
        if (!(cin >> chrInput)) {
            // Display error message to user about the incorrect input
            cout << "Invalid input. Input must be 'y or Y' or 'n or N'. Please try again." << endl;
            // Clear the error flag and ignore the rest of the line
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (chrInput == 'y' || chrInput == 'Y') {
            // Get the input for the dependents
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
        } else if (chrInput == 'n' || chrInput == 'N') {
            // The user has declared they are married status
            return intDependInput;
        } else {
            cout << "Invalid input. Input must be 'y or Y' or 'n or N'. Please try again." << endl;
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

double taxAmount(double& dblGrossIncomeInput)
/*
Function Name: taxAmount
Function Purpose: Function is to calculate the tax amount based off the user input.
*/
{
    // Declare Local Variables
    double dblTaxAmount = 0.0;

    // Set the decimal precision
    cout << fixed << setprecision(2);

    // Calculate the tax amount
    if (dblGrossIncomeInput <= dblFIRST_TIER_MIN) {
        dblTaxAmount = dblGrossIncomeInput * dblFIRST_TIER_PERCENT;
    } else if (dblGrossIncomeInput <= dblSECOND_TIER_MIN) {
        dblTaxAmount = dblGrossIncomeInput * dblSECOND_TIER_PERCENT + dblSECOND_TIER_FIXED_RATE;
    } else {
        dblTaxAmount = dblGrossIncomeInput * dblTHIRD_TIER_PERCENT + dblTHIRD_TIER_FIXED_RATE;
    }

    return dblTaxAmount;
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

void Display_Results(double& dblGrossIncomeInput, double& dblGrossIncomeResult, double& dblTaxAmountResult, 
                    double& dblPensionPercent, double& dblPensionTotal, string& strMaritalStatus, int& intDependentCount)
/*
Function Name: Display_Results
Function Purpose: Function is to display the results.
*/
{
    cout << "----------------------------- Tax Results -----------------------------" << endl;
    cout << setfill('.') << left << setw(40) << "Marital Status: " << right << strMaritalStatus << endl;
    cout << setfill('.') << left << setw(40) << "Total Dependents: " << right  << intDependentCount << endl;
    cout << setfill('.') << left << setw(40) << "Total Pension Percentage: " << right << fixed << setprecision(2) << "%" << dblPensionPercent << endl;
    cout << setfill('.') << left << setw(40) << "Total Pension Saved: " << right << fixed << setprecision(2) << "$" << dblPensionTotal << endl;
    cout << setfill('.') << left << setw(40) << "Total Gross Income Before Tax: " << right << "$"  << dblGrossIncomeInput << endl;
    cout << setfill('.') << left << setw(40) << "Total Tax On Gross Income: " << right << "$"  << dblTaxAmountResult << endl;
    cout << setfill('.') << left << setw(40) << "Total Gross Income After Tax: " << right << fixed << setprecision(2) << "$" << dblGrossIncomeResult << endl;
    cout << endl;
}