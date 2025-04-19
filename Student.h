#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <deque>
#include "Course.h"

struct CompletedCourse {
    Course course;
    std::string semester;
    std::string grade;
};

class Student {
    std::string name;
    std::string id;
    std::string year;
    std::string email;

    std::vector<CompletedCourse> completedCourses;
    std::vector<Course> registeredCourses;
    std::vector<Course> availableCourses;

public:
    Student(std::string name, std::string id,
            std::string year, std::string email);

    void viewGrade() const;

    static double convertGradeToGPA(const std::string &grade);

    double calcGPA() const;

    void showAvailableCourses() const;

    bool checkPrerequisite(const Course &course) const;

    void leftPrerequisites(std::deque<Course> leftCourses) const;

    void registerCourse();

    std::string getName() const { return name; }
    std::string getId() const { return id; }
    std::string getYear() const { return year; }
    std::string getEmail() const { return email; }

    void addCompletedCourse(const CompletedCourse &course);

    void addAvailableCourse(const Course &course);

    const std::vector<Course> &getRegisteredCourses() const { return registeredCourses; }
    const std::vector<Course> &getAvailableCourses() const { return availableCourses; }
    const std::vector<CompletedCourse> &getCompletedCourses() const { return completedCourses; }
};

#endif // STUDENT_H
