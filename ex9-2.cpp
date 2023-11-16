// ----------------------------------------------------------------
// Author: David Teixeira 
// Project: Unit 9 Exercise 9-2
// Course: SDEV-230
// Creation Date: 11/10/2023
// ----------------------------------------------------------------

// Import the Preprocessor Directives
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include <iomanip>
#include <set>

// Provide scope to identifiers inside the standard library
using namespace std;

// Create the constants
const string strInFileName = "Ch9_Ex2Data.txt";
const string strOutFileName = "Ch9_Ex2Out.txt";
const int NAME_COUNT = 20;

// Create Student Struct Type
struct studentType
{
    // Delcare the struct members
    string studentFName;
    string studentLName;
    int testScore;
    char courseGrade;

    // Default constructor 
    studentType() : studentFName(""), studentLName(""), testScore(0), courseGrade(' ') {}

    // Create constructor to initialize members
    studentType(const string& studentFName, const string& studentLName, const int& testScore, const char& courseGrade) :
    studentFName(studentFName), studentLName(studentLName), testScore(testScore), courseGrade(courseGrade) {}
    
};

// Place the headers for each function
void Read_Data_In(studentType& student, istringstream& iss);
void Get_Course_Grade(studentType& student);
void Find_Unique_Test_Scores(studentType aStudents[NAME_COUNT], set<int>& aintUniqueTestScore);
int Set_Test_Score_Array(const set<int>& aintUniqueTestScore);
int Find_Largest_Test_Scores(const int aintScoreList[NAME_COUNT]);
void Output_Results(ofstream& fOut, const studentType aStudents[NAME_COUNT], const int intLargestTestScore);




int main() 
/*
Function Name: main
Function Purpose: This is the main function where the program starts
*/  
{
    // Declare Local Variables
    ifstream fIn;
    ofstream fOut;
    string strLine;
    studentType aStudents[NAME_COUNT];
    set<int> aintUniqueTestScore;
    int intStudentIndex = 0; 

    // Open the files
    fIn.open(strInFileName);
    fOut.open(strOutFileName);

    // For loop checking if the files are open or not
    if (!fIn || !fOut) {
        // If false, the file couldn't open
        cout << "Cannot open file(s)" << strInFileName << endl;
        return 1;
    }

    // Get the line and find the length of the line
    while (getline(fIn, strLine) && intStudentIndex < NAME_COUNT) {
        istringstream iss(strLine);
        // Call the Read_Data_In function and get the data from the .txt file
        Read_Data_In(aStudents[intStudentIndex], iss);
        intStudentIndex++;
    }

    // Process the unique test scores
    Find_Unique_Test_Scores(aStudents, aintUniqueTestScore);

    // Get the largest test score and output results
    int intLargest = Set_Test_Score_Array(aintUniqueTestScore);

    // Display the outputs
    Output_Results(fOut, aStudents, intLargest);

    // Close the files
    fIn.close();
    fOut.close();

    return 0;  
}    

void Read_Data_In(studentType& student, istringstream& iss) {
/*
Function Name: Read_Data_In
Function Purpose: Read the data by each line
*/    
    // Read the student's name (First and Last) and test score
    iss >> student.studentFName >> student.studentLName >> student.testScore;

    // Get the course grade
    Get_Course_Grade(student);
}

void Get_Course_Grade(studentType& student) {
/*
Function Name: Get_Course_Grade
Function Purpose: Get the course grade from the single test score
*/  
    // Determine the grade based off the reference to student.testScore 
    if (student.testScore >= 90) student.courseGrade = 'A';
    else if (student.testScore >= 80) student.courseGrade = 'B';
    else if (student.testScore >= 70) student.courseGrade = 'C';
    else if (student.testScore >= 60) student.courseGrade = 'D';
    else student.courseGrade = 'F';
}

void Find_Unique_Test_Scores(studentType aStudents[NAME_COUNT], set<int>& aintUniqueTestScore) {
/*
Function Name: Find_Unique_Test_Scores
Function Purpose: Get the highest unique course grade from all the students
*/  
    // Find unique test scores
    for (int i = 0; i < NAME_COUNT; i++) {
        aintUniqueTestScore.insert(aStudents[i].testScore); 
    }
}

int Set_Test_Score_Array(const set<int>& aintUniqueTestScore) {
/*
Function Name: Set_Test_Score_Array
Function Purpose: This function sets the score arry with the set of unique test scores
*/    
    // Convert the set to an array 
    int aintScoreArray[NAME_COUNT] = {0}; 
    int index = 0;
    for (int score : aintUniqueTestScore) {
        aintScoreArray[index++] = score;
    }
    return Find_Largest_Test_Scores(aintScoreArray);
}

int Find_Largest_Test_Scores(const int aintScoreList[NAME_COUNT]) {
/*
Function Name: Find_Largest_Test_Scores
Function Purpose: Get the largest course grade from all the students
*/  
    // Delcare Local Variables
    int intLargestScore = 0;

    // Find unique test scores
    for (int i = 0; i < NAME_COUNT; i++) {
        if (aintScoreList[i] > intLargestScore) {
            intLargestScore = aintScoreList[i];
        } 
    }
    
    return intLargestScore;
}


void Output_Results(ofstream& fOut, const studentType aStudents[NAME_COUNT], const int intLargestTestScore) {
/*
Function Name: Output_Results
Function Purpose: Output the results of the students with the highest test scores
*/ 
    // First check if the file is still open, if yes, display first the highest scoring students then all other students
    if (fOut.is_open()) {
        // Output the results for the highest test scores
        fOut << "Students with the highest test score:\n";
        for (int i = 0; i < NAME_COUNT; ++i) {
            if (aStudents[i].testScore == intLargestTestScore) {
                fOut << left << setw(20) << aStudents[i].studentLName + ", " + aStudents[i].studentFName + ", Score: " + to_string(aStudents[i].testScore) + ", Grade: " + aStudents[i].courseGrade + "\n";
            }
        }

        fOut << "\nAll students:\n";
        // Output the results for all students
        for (int i = 0; i < NAME_COUNT; ++i) {
            fOut << left << setw(20) << aStudents[i].studentLName + ", " + aStudents[i].studentFName + ", Score: " + to_string(aStudents[i].testScore) + ", Grade: " + aStudents[i].courseGrade + "\n";
        }
    } else {
        cerr << "Output file is not open." << endl;
    }
}
