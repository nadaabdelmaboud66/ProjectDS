#include "Student.h"
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <utility>

Student::Student(std::string  name, std::string  id,
                 std::string  year, std::string  email)
    : name(std::move(name)), id(std::move(id)), year(std::move(year)), email(std::move(email)) {}

void Student::addCompletedCourse(const CompletedCourse& course) {
    if (convertGradeToGPA(course.grade) == -1) {
        throw std::invalid_argument("Invalid grade provided for completed course");
    }
    completedCourses.push_back(course);
}

void Student::addAvailableCourse(const Course& course) {
    availableCourses.push_back(course);
}

void Student::viewGrade() const {
    if (completedCourses.empty()) {
        std::cout << "No Courses Completed.\n";
        return;
    }

    size_t maxCourseNameWidth = 12;
    size_t maxSemesterWidth = 10;
    size_t maxGradeWidth = 7;

    for (const auto &completedCourse : completedCourses) {
        maxCourseNameWidth = std::max(maxCourseNameWidth, completedCourse.course.getTitle().length());
        maxSemesterWidth = std::max(maxSemesterWidth, completedCourse.semester.length());
        maxGradeWidth = std::max(maxGradeWidth, completedCourse.grade.length());
    }

    std::cout << std::left << std::setw(maxCourseNameWidth) << "Course Name" << " | "
              << std::left << std::setw(maxSemesterWidth) << "Semester" << " | "
              << std::left << std::setw(maxGradeWidth) << "Grade" << "\n";

    std::cout << std::string(maxCourseNameWidth + maxSemesterWidth + maxGradeWidth + 6, '-') << "\n";

    for (const auto &completedCourse : completedCourses) {
        std::cout << std::left << std::setw(maxCourseNameWidth) << completedCourse.course.getTitle() << " | "
                  << std::left << std::setw(maxSemesterWidth) << completedCourse.semester << " | "
                  << std::left << std::setw(maxGradeWidth) << completedCourse.grade << "\n";
    }
}

double Student::convertGradeToGPA(const std::string &grade) {
    if (grade == "A+" || grade == "A") return 4.0;
    if (grade == "A-") return 3.8;
    if (grade == "B+") return 3.7;
    if (grade == "B") return 3.4;
    if (grade == "B-") return 3.1;
    if (grade == "C+") return 2.8;
    if (grade == "C") return 2.5;
    if (grade == "C-") return 2.2;
    if (grade == "D+") return 1.8;
    if (grade == "D") return 1.5;
    if (grade == "D-") return 1.2;
    if (grade == "F") return 0.0;
    return -1; // Invalid grade
}

double Student::calcGPA() const {
    double totalGradePoints = 0;
    double totalCreditHours = 0;

    for (const auto &completedCourse : completedCourses) {
        double gpaGrade = convertGradeToGPA(completedCourse.grade);
        if (gpaGrade != -1) {
            double creditHour = completedCourse.course.getCreditHour();
            totalGradePoints += gpaGrade * creditHour;
            totalCreditHours += creditHour;
        }
    }

    if (totalCreditHours == 0) {
        return 0.0;
    }

    return totalGradePoints / totalCreditHours;
}

void Student::showAvailableCourses() const {
    if (availableCourses.empty()) {
        std::cout << "No available courses to show.\n";
        return;
    }

    for (const auto &course : availableCourses) {
        std::cout << "\n";
        course.showCourseDescription();
    }
}

/*
bool Student::checkPrerequisite(const Course &course) const {
    std::vector<Course> prerequisites = course.getPrerequisites();

    for (const Course &prereq : prerequisites) {
        bool found = false;

        for (const auto &completed : completedCourses) {
            if (completed.course.getCourseID() == prereq.getCourseID()) {
                found = true;
                break;
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}
 */

void Student::leftPrerequisites(std::deque<Course> leftCourses) const {
    if (leftCourses.empty()) {
        std::cout << "You have no remaining prerequisites.\n";
        return;
    }

    std::cout << "❌ You still need to complete the following prerequisites:\n";
    while (!leftCourses.empty()) {
        Course c = leftCourses.front();
        leftCourses.pop_front();
        std::cout << " - " << c.getTitle() << " (ID: " << c.getCourseID() << ")\n";
    }
}

void Student::registerCourse() {
    if (availableCourses.empty()) {
        std::cout << "No courses available for registration.\n";
        return;
    }

    showAvailableCourses();

    std::string courseID;
    std::cout << "Please enter the course ID: ";
    std::cin >> courseID;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    bool found = false;

    for (const auto &course : availableCourses) {
        if (course.getCourseID() == courseID) {
            found = true;

            if (checkPrerequisite(course)) {
                registeredCourses.push_back(course);
                std::cout << "✅ Course \"" << course.getTitle() << "\" registered successfully!\n";
            } else {
                std::cout << "❌ You do not meet the prerequisites for \"" << course.getTitle() << "\".\n";

                std::deque<Course> leftCourses;
                for (const Course &prereq : course.getPrerequisites()) {
                    bool foundPrereq = false;

                    for (const auto &completed : completedCourses) {
                        if (completed.course.getCourseID() == prereq.getCourseID()) {
                            foundPrereq = true;
                            break;
                        }
                    }

                    if (!foundPrereq) {
                        leftCourses.push_back(prereq);
                    }
                }

                leftPrerequisites(leftCourses);
            }
            break;
        }
    }

    if (!found) {
        std::cout << "❌ Course ID not found in available courses.\n";
    }
}