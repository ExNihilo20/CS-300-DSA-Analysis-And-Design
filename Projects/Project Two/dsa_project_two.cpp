//============================================================================
// Name        : DSA_project_two.cpp
// Author      : AlexCreznic
// Version     : 1.0
// Copyright   : No Copyright
// Description : ABCU C++ Program
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using namespace std;

// Structure to represent a course
struct Course {
    string code;
    string title;
    vector<string> prerequisites;
};

// Custom comparison function for sorting courses by their code
bool compareCourses(const Course& course1, const Course& course2) {
    return course1.code < course2.code;
}

void loadCourseData(unordered_map<string, Course>& courseMap, string filename) {
    ifstream file(filename); // Open the file for reading
    if (file.is_open()) { // Check if the file was successfully opened
        string line;

        while (getline(file, line)) { // Read each line from the file
            stringstream ss(line);
            string code, title, prerequisitesString;
            if (getline(ss, code, ',') && getline(ss, title, ',')) { // Split the line into code and title
                vector<string> prerequisites;
                while (getline(ss, prerequisitesString, ',')) { // Split the prerequisites string into individual prerequisites
                    prerequisites.push_back(prerequisitesString);
                }

                Course newCourse; // new instance of the Course structure named
                newCourse.code = code; // object represents a single course with properties like code, title, and prerequisites
                newCourse.title = title; // '' for title
                newCourse.prerequisites = prerequisites; // '' for prerequisites

                courseMap[code] = newCourse; // Add the course to the courseMap using the course code as the key
            } else {
                cout << "Error: Invalid line format in the file" << endl;
            }
        }
        file.close(); // Close the file
    } else {
        cout << "Error: Unable to open the file" << endl; // if unable to open the file
    }
}

// Function to search for a course and print its information and prerequisites
void searchCourse(const unordered_map<string, Course>& courseMap, string courseCode) {
    // Check if the course with the given courseCode exists in the courseMap
    if (courseMap.count(courseCode) > 0) {
        // Retrieve the reference to the Course object using the courseCode as the key
        const Course& course = courseMap.at(courseCode);

        cout << course.code << ", " << course.title << endl; // Print the course code and title
        cout << "Prerequisites: ";

        if (course.prerequisites.empty()) { // Check if the course has any prerequisites
            cout << "None";// If there are no prerequisites, print "None"
        } else {
            // Print each prerequisite separated by a space
            for (const string& prerequisite : course.prerequisites) {
                cout << prerequisite << " ";
            }
        }
        cout << endl; // Print a new line after printing the prerequisites
    } else {
        cout << "Course not found." << endl;  // If the course is not found in the courseMap, print an error message
    }
}

// Function to print the course list in alphanumeric order for the Computer Science department
void printCourseList(const unordered_map<string, Course>& courseMap) {
    // Create a vector to store the courses for sorting
    vector<Course> sortedCourses;

    // Copy the courses from the map to the vector
    for (const auto& pair : courseMap) {
        sortedCourses.push_back(pair.second);
    }

    // Sort the courses based on their code using the custom comparison function
    sort(sortedCourses.begin(), sortedCourses.end(), compareCourses);

    // Print the sorted course list
    cout << "Here is a sample schedule:" << endl;
    for (const auto& course : sortedCourses) {
        cout << course.code << ", " << course.title << endl;
    }
    cout << endl;
}

int main() {
    // Create an unordered_map to store the courses
    unordered_map<string, Course> courseMap;

    // Specify the file name containing the course data
    string filename = "abcu.txt";

    // Declare variables for user input
    string courseCode;
    string inputCourseCode;


    cout << "Welcome to the course planner." << endl; // Print the welcome message
    cout << endl;

    // Start the main program loop
    while (true) {
        // Print the menu options
        cout << "   1. Load Data Structure." << endl;
        cout << "   2. Print Course List." << endl;
        cout << "   3. Print Course." << endl;
        cout << "   4. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        // Read the user's input
        int userInput;
        cin >> userInput;

        // Process the user's choice
        switch (userInput) {
            case 1:
                // Load the course data from the file into the courseMap
                loadCourseData(courseMap, filename);
                break;
            case 2:
                // Print the course list in alphabetical order
                printCourseList(courseMap);
                break;
            case 3:
                cout << "What course do you want to know about? ";

                // Read the course code input from the user
                cin >> inputCourseCode;

                // Convert the input to uppercase
                transform(inputCourseCode.begin(), inputCourseCode.end(), inputCourseCode.begin(), ::toupper);
                searchCourse(courseMap, inputCourseCode); // Search for and print the information about the course
                break;
            case 4:
                // Exit the program
                cout << "Thank you for using the course planner!" << endl;
                return 0;
            default:
                // Print an error message for an invalid option
                cout << userInput << " is not a valid option." << endl;
                break;
        }
    }
    return 0;
}
