#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Course structure to hold course information
struct Course {
    string courseNumber;
    string title;
    vector<string> prerequisites;

    // Function to display course information
    void display() const {
        cout << "Course Number: " << courseNumber << endl;
        cout << "Title: " << title << endl;
        cout << "Prerequisites: ";
        if (prerequisites.empty()) {
            cout << "None";
        } else {
            for (const auto& prereq : prerequisites) {
                cout << prereq << " ";
            }
        }
        cout << endl;
    }
};

// Function to load courses from a file into a vector
bool loadCourses(const string& filename, vector<Course>& courses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Course course;
        getline(ss, course.courseNumber, ',');
        getline(ss, course.title, ',');

        string prereq;
        while (getline(ss, prereq, ',')) {
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq);
            }
        }
        courses.push_back(course);
    }
    file.close();
    return true;
}

// Function to print all courses in alphanumeric order
void printCourses(const vector<Course>& courses) {
    vector<Course> sortedCourses = courses;
    sort(sortedCourses.begin(), sortedCourses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
    });

    cout << "Alphanumeric Course List:" << endl;
    for (const auto& course : sortedCourses) {
        cout << course.courseNumber << ": " << course.title << endl;
    }
}

// Function to find and print a specific course's information
void printCourseInfo(const vector<Course>& courses, const string& courseNumber) {
    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            course.display();
            return;
        }
    }
    cout << "Error: Course " << courseNumber << " not found." << endl;
}

// Main function to run the advising assistance program
int main() {
    vector<Course> courses;
    string filename;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Load course data from file" << endl;
        cout << "2. Print alphanumeric list of courses" << endl;
        cout << "3. Print course information" << endl;
        cout << "9. Exit" << endl;
        cout << "Select an option: ";
        
        int option;
        cin >> option;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (option) {
            case 1:
                cout << "Enter the filename: ";
                getline(cin, filename);
                if (loadCourses(filename, courses)) {
                    cout << "Courses loaded successfully." << endl;
                }
                break;
            case 2:
                printCourses(courses);
                break;
            case 3: {
                cout << "Enter the course number: ";
                string courseNumber;
                getline(cin, courseNumber);
                printCourseInfo(courses, courseNumber);
                break;
            }
            case 9:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Error: Invalid option. Please try again." << endl;
        }
    }
}
