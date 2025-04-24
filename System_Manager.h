//
// Created by msi on 20/04/2025.
//

#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#include "Student.h"
#include "Course.h"
#include"Admin.h"
#include <iostream>
#include <vector>
#include <stack>
//#include <pair>
#include <utility>
#include <unordered_map>
#include <map>
#include <string>
#include <set>
using namespace std;

class System_Manager {
string username;
string password;

unordered_map<string, Student> students;
unordered_map<string, Course> courses;  //remove ?
unordered_map<string, Admin> admins;

public:
System_Manager();


void editAdminPass(string username, string password);
void editStudentPass(string username, string password);
void showAvailableCourses();
void showEligibleCourses(string id);
bool isStudentEligible(string id, string courseCode);
Student getStudent(string id);
Admin getAdmin(string username);
Course getCourse(string courseID);


//--------------------------------------------- FILES FUNCTIONS---------------------------------------------

void readStudentsFromFile();
void writeStudentsToFile();

void readAdminsFromFile();
void writeAdminsToFile();

void readCoursesFromFile();  
void writeCoursesToFile();



};



#endif //SYSTEM_MANAGER_H
