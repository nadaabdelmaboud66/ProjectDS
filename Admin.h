
#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
using namespace std;




class Admin {


    string id;
    string name;
    string username;
    string password;
    stack <string> addedcourses;

    Admin();
    Admin(string id , string name , string username , string password  );


    // managing courses 
    // can upload(add) or update 
    void addCourse(System_Manager & manager);
    void updateCourse(System_Manager & manager);
    void removeCourse(System_Manager & manager);
    bool  UniqueID ( string , char );
    // extra features
    void undoLastaddedcourse (System_Manager & manager);
    void displayCoursesByCreditHours(System_Manager & manager);



    // managing prerequistes
    // add new prerequisite for a course
    void addPrereq();
    void removePrereq();


 // managing grades 
    // can upload(add) or update 
    void addgrade();
    void updategrade();


    // add new student 
    void addStudent();



};



#endif //ADMIN_H
