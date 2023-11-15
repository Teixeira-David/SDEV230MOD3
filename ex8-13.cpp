// ----------------------------------------------------------------
// Author: David Teixeira 
// Project: Unit 8 Exercise 8-13
// Course: SDEV-230
// Creation Date: 11/10/2023
// ----------------------------------------------------------------

// Import the Preprocessor Directives
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <iomanip>

// Provide scope to identifiers inside the standard library
using namespace std;

// Create the constants
const string strFileName = "ch8_Ex13Data.txt";
const int NAME_COUNT = 10;
const int SCORE_COUNT = 5;

// Place the headers for each function
void Read_Data_In(string &strName, int aintScoreList[], istringstream& iss);
void Calculate_Average_and_Grade(int aintScoreList[], double& dblAverage, char& chrGrade);
void Output_Results(const string astrNameList[], const int aintScoreList[][SCORE_COUNT], const double dblAverageGrades[], const char chrGrades[]);
double Calculate_Class_Average(const double dblAverageGrades[]);

int main() 
{
    // Declare Local Variables
    ifstream fIn;
    string strLine;
    string astrNameList[NAME_COUNT];
    int aintScoreList[NAME_COUNT][SCORE_COUNT];
    char chrGrades[NAME_COUNT];
    double dblAverageGrades[NAME_COUNT];
    double dblClassAverage = 0.0;
    int intStudentIndex = 0;

//  string astrStudentData[NAME_COUNT] = {
//      "Johnson 85 83 77 91 76",
//      "Aniston 80 90 95 93 48",
//      "Cooper 78 81 11 90 73",
//      "Gupta 92 83 30 69 87",
//      "Blair 23 45 96 38 59",
//      "Clark 60 85 45 39 67",
//      "Kennedy 77 31 52 74 83",
//      "Bronson 93 94 89 77 97",
//      "Sunny 79 85 28 93 82",
//      "Smith 85 72 49 75 63"
//  };
    // Open the file
    fIn.open(strFileName);
    if (!fIn) {
        // If false, the file couldn't open
        cout << "Cannot open file " << strFileName << endl;
        return 1;
    }

    // Get the line and find the length of the line
    while (getline(fIn, strLine) && intStudentIndex < NAME_COUNT) {
        istringstream iss(strLine);
        // Call the Read_Data_In function and pass by ref the name list array, by value the score list, and the string stream
        Read_Data_In(astrNameList[intStudentIndex], aintScoreList[intStudentIndex], iss);
        // Call Calculate_Average_and_Grade and pass in the score list by value, the average grade list and chrGrade variable by ref
        Calculate_Average_and_Grade(aintScoreList[intStudentIndex], dblAverageGrades[intStudentIndex], chrGrades[intStudentIndex]);
        intStudentIndex++;
    }

//  // Loop over the hardcoded student data
//  for (intStudentIndex = 0; intStudentIndex < NAME_COUNT; intStudentIndex++) {
//      istringstream iss(astrStudentData[intStudentIndex]);
//      Read_Data_In(astrNameList[intStudentIndex], aintScoreList[intStudentIndex], iss);
//      Calculate_Average_and_Grade(aintScoreList[intStudentIndex], dblAverageGrades[intStudentIndex], chrGrades[intStudentIndex]);
//  }

    // Close the file
    fIn.close();

    // Output the results
    Output_Results(astrNameList, aintScoreList, dblAverageGrades, chrGrades);

    // Get the class average
    dblClassAverage = Calculate_Class_Average(dblAverageGrades);

    // Display the results
    cout << "\n" << endl;
    cout << "Class Average Score = " << fixed << setprecision(2) << dblClassAverage << endl;

    return 0;  
}    

void Read_Data_In(string& strName, int aintScoreList[], istringstream& iss) {
/*
Function Name: Read_Data_In
Function Purpose: Read the data by each line
*/    
    // Read the student's name
    iss >> strName; // strName holds the name of the student
    
    // Read the student's scores
    for (int j = 0; j < SCORE_COUNT; j++) {
        iss >> aintScoreList[j]; // Add the scores to the array variable. 
    }
}

void Calculate_Average_and_Grade(int aintScoreList[], double& dblAverage, char& chrGrade) {
/*
Function Name: Calculate_Average_And_Grade
Function Purpose: Calculate the average score and get the grade
*/  
    // Declare Local Variables
    int intSum = 0;

    // For loop getting the sum of the scores 
    for (int i = 0; i < SCORE_COUNT; i++) {
        intSum += aintScoreList[i];
    }
    // Calculate the average score. Convert the int to double
    dblAverage = static_cast<double>(intSum) / SCORE_COUNT;

    // Determine the grade based off the average. The reference of chrGrade is update outside of local scope
    if (dblAverage >= 90) chrGrade = 'A';
    else if (dblAverage >= 80) chrGrade = 'B';
    else if (dblAverage >= 70) chrGrade = 'C';
    else if (dblAverage >= 60) chrGrade = 'D';
    else chrGrade = 'F';
}

void Output_Results(const string astrNameList[], const int aintScoreList[][SCORE_COUNT], 
    const double dblAverageGrades[], const char chrGrades[]) {
/*
Function Name: Output_Results
Function Purpose: Output the results
*/ 
    // For loop to output the results from the passed by ref arrays
    for (int i = 0; i < NAME_COUNT; i++) {
        cout << astrNameList[i] << ": Scores = ";
        for (int j = 0; j < SCORE_COUNT; j++) {
            cout << aintScoreList[i][j] << " ";
        }
        cout << "Average = " << fixed << setprecision(2) << dblAverageGrades[i] << ", Grade = " << chrGrades[i] << endl;
    }
}

double Calculate_Class_Average(const double dblAverageGrades[]) {
/*
Function Name: Calculate_Class_Average
Function Purpose: Calculate the class average
*/ 
    // Delcare Local Variables
    double dblSum = 0;

    // For loop to get the average score and update return the result
    for (int i = 0; i < NAME_COUNT; i++) {
        dblSum += dblAverageGrades[i];
    }
    // Return the average sum
    return dblSum / NAME_COUNT;
}