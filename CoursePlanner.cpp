//============================================================================
// Name        : CoursePlanner.cpp
// Author      : Cruz
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>



using namespace std;

//Define class Course
class Course {
public:
    string courseNumber;
    string title;
    vector<string> prerequisites;

    Course(const string& num, const string& tit) : courseNumber(num), title(tit) {}

    void addPrerequisite(const string& prerequisite) {
        prerequisites.push_back(prerequisite);
    }
};

vector<Course> readCoursesFromFile(const string& filename) {
    vector<Course> courses;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
    	cout << "File is open"<< endl;
        while (getline(file, line)) {
            istringstream iss(line);
            string num, tit;
            getline(iss, num, ',');
            getline(iss, tit, ',');
            Course newCourse(num, tit);

            string prereq;
            while (getline(iss, prereq, ',')) {
                newCourse.addPrerequisite(prereq);
            }
            courses.push_back(newCourse);
        }
        file.close();
    } else {
        cerr << "Failed to open file: " << filename << endl;
    }
    return courses;
}
//Function to sort and print the courses
void sortAndPrintCourses(vector<Course>& courses) {
    sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {
        return a.courseNumber < b.courseNumber;
    });
    for (const auto& course : courses) {
        cout << course.courseNumber << ", " << course.title << "\n";
    }
}
//Function to print the course details
void printCourseDetails(const vector<Course>& courses, const string& courseNumber) {
    auto it = find_if(courses.begin(), courses.end(), [&courseNumber](const Course& course) {
        return course.courseNumber == courseNumber;
    });
    if (it != courses.end()) {
        cout << it->courseNumber << ", " << it->title << "\nPrerequisites: ";
        if (it->prerequisites.empty()) {
            cout << "No prerequisites\n";
        } else {
            for (const auto& prereq : it->prerequisites) {
                cout << prereq;
                if (&prereq != &it->prerequisites.back()) cout << ", ";
            }
            cout << "\n";
        }
    } else {
        cout << "Course not found.\n";
    }
}
//Function to print Menu
void printMenu() {
    cout << "\n1. Load Data Structure.\n"
         << "2. Print Course List.\n"
         << "3. Print Course.\n"
         << "9. Exit\n"
         << "What would you like to do? ";
}

//Main function
int main() {
    vector<Course> courses;
    string filename;
    int choice;

    cout << "Welcome to the course planner.\n";
    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter filename: ";
                cin >> filename;
                courses = readCoursesFromFile(filename);
                cout << "Data loaded successfully.\n";
                break;
            case 2:
                cout << "Here is a sample schedule:\n";
                sortAndPrintCourses(courses);
                break;
            case 3:
                cout << "What course do you want to know about? ";
                cin >> filename; // reuse filename string variable for course number input
                printCourseDetails(courses, filename);
                break;
            case 9:
                cout << "Thank you for using the course planner!\n";
                return 0;
            default:
                cout << choice << " is not a valid option.\n";
                break;
        }
    }
    return 0;
}
