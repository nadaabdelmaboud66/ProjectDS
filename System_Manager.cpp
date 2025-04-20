//
// Created by msi on 20/04/2025.
//

#include "System_Manager.h"

void System_Manager::editAdminPass(string username, string password) {

    int i = 3;
    while (i--) {
        if (admins.find(username) == admins.end()) {
            cout << "This username does not exist." << endl;
            return;
        } else {
            string oldPassword;
            cout << "Enter your old password:" << endl;
            cin >> oldPassword;
            if (admins[username] == oldPassword) {
                admins[username] = password;
                cout << "Password successfully changed." << endl;
                return;
            } else {
                cout << "Password is incorrect." << endl;
            }
        }
    }

    cout << "Too many tries, try again later." << endl;
}


void System_Manager::editStudentPass(string id, string password) {
    int i = 3;
    while (i--) {
        if (students.find(id) == students.end()) {
            cout << "This ID does not exist." << endl;
            return;
        } else {
            string oldPassword;
            cout << "Enter your old password:" << endl;
            cin >> oldPassword;
            if (students[id] == oldPassword;) {
                students[id] = password;
                cout << "Password successfully changed." << endl;
                return;
            } else {
                cout << "Password is incorrect." << endl;
            }
        }
    }

    cout << "Too many tries, try again later." << endl;
}

Student System_Manager::getStudent(string id) {
    return students[id];
}

Admin System_Manager::getAdmin(string username) {
    return admins[username];
}

Course System_Manager::getCourse(string courseID) {
    return courses[courseID];
}

void System_Manager::showAvailableCourses() {
    cout << "Available courses:" << endl;
    for(auto course : courses) {
        cout << "Course ID: " << course.getCourseID() << endl;
        cout << "Title: " << course.getTitle() << endl;
        cout << "Credit Hours: " << course.getCreditHour() << endl;
        cout << "Instructor: " << course.getInstructorName() << endl;
        cout << "Syllabus: " << course.getSyllabus() << endl;

    }
}

void System_Manager::showEligibleCourses(string id) {
    if (students.find(id) == students.end()) {
        cout << "Invalid entry." << endl;
    } else {
        Student student = students[id];
        stack<Course> eligibleCourses;

        for (const auto& [courseID, course] : courses) {
            bool eligible = true;

            for (auto prereq : course.getPrerequisites()) {
                bool found = false;

                string CourseID = prereq.getCourseID();
                    if (student.completedCourses.find(CourseID) != student.completedCourses.end()) {
                        found = true;
                    }

                if (!found) {
                    eligible = false;
                    break;
                }
            }

            if (eligible) {
                eligibleCourses.push(course);
            }
        }

        // Display eligible courses
        if (eligibleCourses.empty()) {
            std::cout << "No eligible courses found for " << student.getName() << ".\n";
            return;
        }

        cout << "Eligible courses for " << student.getName() << ":\n";
        while (!eligibleCourses.empty()) {
            eligibleCourses.top().showCourseDescription();
            eligibleCourses.pop();
        }

    }
}

bool isStudentEligible(string id, string courseCode) {
    if (students.find(id) == students.end() || courses.find(courseCode) == courses.end()) {
        return false;
    }

    Student student = students[id];
    Course course = courses[courseCode];

    for (const Course& prereq : course.getPrerequisites()) {
        string prereqID = prereq.getCourseID();
        if (student.completedCourses.find(prereqID) == student.completedCourses.end()) {
            return false;
        }
    }

    return true;
}
