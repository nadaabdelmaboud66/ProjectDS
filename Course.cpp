#include "Course.h"
#include <iomanip>

Course::Course() : courseDescription{"", "", 0, {"", ""}} {
}

Course::Course(const std::string &id, const CourseDescription &desc)
    : courseID(id), courseDescription(desc) {
}

std::string Course::getCourseID() const {
    return courseID;
}

CourseDescription Course::getDescription() const {
    return courseDescription;
}

std::string Course::getTitle() const {
    return courseDescription.title;
}

std::string Course::getSyllabus() const {
    return courseDescription.syllabus;
}

int Course::getCreditHour() const {
    return courseDescription.creditHour;
}

Instructor Course::getInstructor() const {
    return courseDescription.instructor;
}

std::string Course::getInstructorName() const {
    return courseDescription.instructor.name;
}

std::string Course::getInstructorEmail() const {
    return courseDescription.instructor.email;
}

const std::vector<Course> &Course::getPrerequisites() const {
    return prerequisites;
}

void Course::setCourseID(const std::string &id) {
    courseID = id;
}

void Course::setDescription(const CourseDescription &desc) {
    courseDescription = desc;
}

void Course::setTitle(const std::string &t) {
    courseDescription.title = t;
}

void Course::setSyllabus(const std::string &s) {
    courseDescription.syllabus = s;
}

void Course::setCreditHour(int ch) {
    if (ch < 0) {
        throw std::invalid_argument("Credit hours cannot be negative");
    }
    courseDescription.creditHour = ch;
}

void Course::setInstructor(const Instructor &inst) {
    courseDescription.instructor = inst;
}

void Course::setInstructorName(const std::string &name) {
    courseDescription.instructor.name = name;
}

void Course::setInstructorEmail(const std::string &email) {
    courseDescription.instructor.email = email;
}

void Course::addPrerequisite(const Course &course) {
    // Prevent circular dependencies
    if (course.getCourseID() == courseID) {
        throw std::invalid_argument("A course cannot be a prerequisite for itself");
    }
    prerequisites.push_back(course);
}

void Course::clearPrerequisites() {
    prerequisites.clear();
}

void Course::showCourseDescription() const {
    constexpr size_t LABEL_WIDTH = 20;
    constexpr size_t VALUE_WIDTH = 40;

    std::cout << std::left << std::setw(LABEL_WIDTH) << "Course ID:"
            << std::setw(VALUE_WIDTH) << courseID << "\n"
            << std::setw(LABEL_WIDTH) << "Title:"
            << std::setw(VALUE_WIDTH) << courseDescription.title << "\n"
            << std::setw(LABEL_WIDTH) << "Instructor:"
            << std::setw(VALUE_WIDTH) << courseDescription.instructor.name << "\n"
            << std::setw(LABEL_WIDTH) << "Email:"
            << std::setw(VALUE_WIDTH) << courseDescription.instructor.email << "\n"
            << std::setw(LABEL_WIDTH) << "Credit Hours:"
            << std::setw(VALUE_WIDTH) << courseDescription.creditHour << "\n"
            << std::setw(LABEL_WIDTH) << "Syllabus:"
            << std::setw(VALUE_WIDTH) << courseDescription.syllabus << "\n\n";
}

void Course::showPrerequisites() const {
    if (prerequisites.empty()) {
        std::cout << "No prerequisites for this course.\n\n";
        return;
    }

    std::cout << "Prerequisites for " << courseID << " - " << courseDescription.title << ":\n";
    for (const auto &prereq: prerequisites) {
        std::cout << " - " << prereq.getCourseID() << ": " << prereq.getTitle() << "\n";
    }
    std::cout << "\n";
}
