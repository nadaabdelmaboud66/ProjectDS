
#include "Admin.h"
#include "System_Manager.h"
#include "Course.h" 

Admin :: Admin (){
    id = name = username = password = "";
}

Admin :: Admin(string id , string name , string username , string password ){
    this->id = id;
    this->name = name ;
    this->username = username ;
    this->password = password ;
}


bool Admin :: UniqueID( string ID , char type ){

    System_Manager manager;
if( type == 'C'){

    if(manager.courses.find(ID) == manager.courses.end()){
        // id is unique 
        return true;
    }

    return false ;

}

else if(type == 'S'){

    if(manager.students.find(ID) == manager.students.end()){
        // id is unique 
        return true;
    }

    return false ;


}

return false ;
}

  void Admin :: addCourse(System_Manager &manager){

    cout << "Please Enter a Detailed course Description of the following :" << "\n";
    cout << "1. Unique course id " << "\n" << "2. title " << "\n" << "3.syllabus" << "\n" << "4.credithour" << "\n" << "5.instructorName" << "\n" << "6.Instructor Email " << "\n";
    string courseID , title , syllabus  , instructorName , instructorEmail;
    int credithour;

    cout << "Enter unique course ID: ";
    cin >> courseID;

    while (!UniqueID(courseID, 'C')) {
        cout << "This ID is already taken. Please Try Again: ";
        cin >> courseID;
    }
    // check if the id is unique 

    cin.ignore(); // Clear newline buffer
    cout << "Enter course title: ";
    getline(cin, title);

    cout << "Enter syllabus: ";
    getline(cin, syllabus);

    cout << "Enter credit hours: ";
    cin >> credithour;
    cin.ignore();

    cout << "Enter instructor name: ";
    getline(cin, instructorName);

    cout << "Enter instructor email: ";
    getline(cin, instructorEmail);


    
            Instructor I = {instructorName , instructorEmail};
            CourseDescription desc = { title , syllabus , credithour , I };
            Course newCourse (courseID , desc );
           // course[courseID] = newCourse ;
            manager.courses[courseID] = newCourse ;
            addedcourses.push(courseID);
            cout << "The course was added successfully. "<<"\n";
           

      


}



void Admin :: updateCourse(System_Manager& manager ){


    cout << "Please Enter the course ID you want to Update  " << "\n";
    string courseID ;
    cin >> courseID;

    if(manager.courses.find(courseID) == manager.courses.end()){
        cout << "course not found." << '\n';
        return;
    }

    Course& courseToUpdate = manager.getCourse(courseID);

    cout << "what would you like to update "<< "\n";
    cout << "Choice 1 :  courseID "   << "\n" << "Choice 2 :title " << "\n" << "Choice 3 :syllabus " << "\n" << "Choice 4 :credithour " << "\n" << "Choice 5: instructorName " << "\n" << "Choice 6: instructorEmail" << "\n";
    
    int choice ; cin >> choice ;
    cin.ignore();

    switch (choice){

    case 1:
    string newID ;
    cout << "Enter new course ID: ";
    cin >> newID;
    if(UniqueID(newID , 'C')){
        courseToUpdate.setCourseID(newID);
        manager.courses[newID] = coursToUpdate ;
        manager.courses.erase(courseID);
        cout << "Course ID updated successfully."<< "\n";
    }
    else 
    cout << "this Course ID is already taken " << "\n";

    break;


    case 2:
    cout <<  "Enter new title: " ;
    string newTitle  ; getline(cin, newTitle);
    courseToUpdate.setTitle(newTitle);
 

    break;

    case 3:
    cout << "Enter new syllabus: ";
    string newsyllabus ; getline(cin, newSyllabus);
    courseToUpdate.setSyllabus(newsyllabus) ;
   
    break;


    case 4:
    cout << "Enter new credit hours: ";
    int newcredithour ; cin >> newcredithour;
    courseToUpdate.setCreditHour(newcredithour);
   
    break;



    case 5:
    cout << "Enter new instructor name: ";
        string newInstName ; getline(cin, newInstName);
    courseToUpdate.setInstructorName(newInstName);
    
    break;


    case 6:
    cout << "Enter new instructor email: ";
    string newInstEmail ; getline(cin, newInstEmail);
    courseToUpdate.setInstructorEmail(newInstEmail);
    
    break;

    

    default: 
   
    cout << "Invalid choice."<< '\n';
    return;







    }
    


    cout << "the course was updated successfully"<<"\n";


}



void Admin :: removeCourse(System_Manager& manager){
// remove multiple courses in one go 
vector <string > courseIDs ;
    cout << "Please Enter the course IDs you want to remove (type 'done' to finish ) :" << "\n";

    string input ;cin >>input;
    while(cin >> input && input != 'done'){

         if(manager.courses.find(id) == manager.courses.end())
         cout << "course not found " << '\n';

         else 
         courseIDs.push_back(input);
        
    
}

    char confirm ;

    for( auto string id : courseIDs){
    cout << "Are you sure you want to delete this course?  " << id << "  (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        manager.courses.erase(id);
        cout << "Course removed successfully." << "\n";
    } else {
        cout << "Deletion cancelled." << "\n";
    }
}
}



void Admin :: undoLastaddedcourse(System_Manager & manager){
    if(addedcourses.empty()){
        cout << "No  Recently added courses to undo" << '\n';
        return;
    }

    string lastCourseID = addedCourses.top();
    addedCourses.pop();

    // Check if it still exists before erasing
    if (manager.courses.find(lastCourseID) != manager.courses.end()) {
        manager.courses.erase(lastCourseID);
        cout << "Undo successful. Course with ID " << lastCourseID << " has been removed." << '\n';
    } else {
        cout << "Course ID " << lastCourseID << " was already removed manually." << '\n';
    }
}



//takes time better not to  use it 
void Admin :: displayCoursesByCreditHours(System_Manager & manager){
    if(manager.course.empty()){
        cout << "No courses availble ." << '\n';
    }

    map <int , vector<string> > coursesbycredit ; // <hours, course IDs>

    for(auto [courseID , course]  :  manager.courses){
        coursesbycredit[course.getCreditHour].push_back(courseID);
    }

    for(auto [credit , courseIDs] : coursesbycredit){
        cout << "=== " << credit << " Credit Hour Course(s) === " << '\n';
        for (auto string id : courseIDs) {
            cout << "- " << id << ": " << manager.courses[id].getTitle() << '\n';
        }

        cout << '\n';
    }

}



