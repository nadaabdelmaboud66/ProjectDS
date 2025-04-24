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


//--------------------------------------------- FILES FUNCTIONS---------------------------------------------

//Students Functions

void System_Manager::readStudentsFromFile() {
    std::ifstream file("students.csv");
    if (!file.is_open()) {
        std::cerr << " Failed to open file for reading:students.csv \n " ;
        return;
    }

    students.clear();
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, id, year, email, gpaStr, creditHoursStr, completedStr, registeredStr;

        std::getline(ss, name, ',');
        std::getline(ss, id, ',');
        std::getline(ss, year, ',');
        std::getline(ss, email, ',');
        std::getline(ss, gpaStr, ',');
        std::getline(ss, creditHoursStr, ',');
        std::getline(ss, completedStr, ',');
        std::getline(ss, registeredStr, ',');

        Student student(name, id, year, email);

        // Parse completed courses

        std::stringstream completedStream(completedStr);
        std::string courseID;
        while (std::getline(completedStream, courseID, '|')) {
            Course* c = getCourseByID(courseID); 
            if (c) {
                CompletedCourse cc(*c, "N/A", "A"); 
                student.addCompletedCourse(cc);
            }
        }

        // Parse registered courses
        std::stringstream regStream(registeredStr);
        while (std::getline(regStream, courseID, '|')) {
            Course* c = getCourseByID(courseID);
            if (c) {
                student.addAvailableCourse(*c); 
                student.registerCourse(); 
            }
        }

        student.setCompletedCreditHours(std::stoi(creditHoursStr));
        students.push_back(student);
    }

    file.close();
}


void System_Manager::writeStudentsToFile() {
    std::ofstream file("students.csv");
    if (!file.is_open()) {
        std::cerr << " Failed to open file for writing:students.csv\n ";
        return;
    }

    for (const auto& student : students) {
        file << student.getName() << ","
             << student.getID() << ","
             << student.getYear() << ","
             << student.getEmail() << ","
             << std::fixed << std::setprecision(2) << student.calcGPA() << ","
             << student.getCompletedCreditHours() << ",";

        // Completed Courses IDs
        for (size_t i = 0; i < student.getCompletedCourses().size(); ++i) {
            file << student.getCompletedCourses()[i].course.getCourseID();
            if (i != student.getCompletedCourses().size() - 1)
                file << "|";
        }
        file << ",";

        // Registered Courses IDs
        for (size_t i = 0; i < student.getRegisteredCourses().size(); ++i) {
            file << student.getRegisteredCourses()[i].getCourseID();
            if (i != student.getRegisteredCourses().size() - 1)
                file << "|";
        }

        file << "\n";
    }

    file.close();
}



//Admins Functions

void System_Manager::readAdminsFromFile() {
    std::ifstream file("admins.csv"); 
    if (!file.is_open()) {
        std::cerr << " Failed to open file for reading: admins.csv\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name, id, username, password;

        std::getline(ss, name, ',');
        std::getline(ss, id, ',');
        std::getline(ss, username, ',');
        std::getline(ss, password, ',');

        
        Admin admin(id, name, username, password);
        admins[username] = admin; 
    }

    file.close();
}

void System_Manager::writeAdminsToFile() {
    std::ofstream file("admins.csv");  
    if (!file.is_open()) {
        std::cerr << " Failed to open file for writing: admins.csv\n";
        return;
    }

    for (const auto& entry : admins) {
        const Admin& admin = entry.second;
        file << admin.getName() << ","
             << admin.getID() << ","
             << admin.getUsername() << ","
             << admin.getPassword() << "\n";
    }

    file.close();
}





//Courses Function

void System_Manager::readCoursesFromFile() {
    std::ifstream file("courses.csv");
    if (!file.is_open()) {
        std::cerr << " Failed to open courses.csv for reading\n";
        return;
    }

    courses.clear(); 
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, title, creditStr, instructorName, instructorEmail, prereqStr;

        std::getline(ss, id, ',');
        std::getline(ss, title, ',');
        std::getline(ss, creditStr, ',');
        std::getline(ss, instructorName, ',');
        std::getline(ss, instructorEmail, ',');
        std::getline(ss, prereqStr, ',');

        Instructor inst{instructorName, instructorEmail};
        CourseDescription desc{title, "", std::stoi(creditStr), inst};
        Course course(id, desc);

        std::stringstream prereqStream(prereqStr);
        std::string prereqID;
        while (std::getline(prereqStream, prereqID, '|')) {
            Course prereq(prereqID, {});
            course.addPrerequisite(prereq);
        }

        courses[id] = course;
    }

    file.close();
}


void System_Manager::writeCoursesToFile() {
    std::ofstream file("courses.csv");
    if (!file.is_open()) {
        std::cerr << " Failed to open courses.csv for writing\n";
        return;
    }

    for (const auto& [id, course] : courses) {
        file << id << ","
             << course.getTitle() << ","
             << course.getCreditHour() << ","
             << course.getInstructorName() << ","
             << course.getInstructorEmail() << ",";

        const auto& prereqs = course.getPrerequisites();
        for (size_t i = 0; i < prereqs.size(); ++i) {
            file << prereqs[i].getCourseID();
            if (i != prereqs.size() - 1)
                file << "|";
        }

        file << "\n";
    }

    file.close();
}

