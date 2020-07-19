#include "LeafMenu.h"

#include <utility>

using namespace std;

LeafMenu::LeafMenu(std::string name, Menu* parent,std::function<void(Controller&)> functionality)
    : Menu{move(name), parent}, functionality(std::move(functionality)) {}

void LeafMenu:: showSubMenus() const {}

void LeafMenu::run() {
    setCurrentMenu(parent);
    functionality(Menu::controller);
    /*
    if(name == "Show This Semester Courses"){

    }

    else if(name == "Take Course"){
        string ID;
        cout << "Enter student ID: ";
        cin >> ID;
        string course;
        cout << "Enter course name: ";
        cin >> course;
        controller.takeCourse(ID,course);
    }

    else if(name == "Drop Course"){
    }

    else if(name == "Show Student Courses In Current Semester"){

    }

    else if(name == "Calculate Student Salary"){

    }

    else if(name == "Show Professor Courses In Current Semester"){

    }

    else if(name == "Submit Grade"){

    }

    else if(name == "Calculate Professor Salary"){

    }

    else if(name == "Add Professor"){
        string ID;
        cout << "Enter Professor number: ";
        cin >> ID;
        string first;
        cout << "Enter First Name: ";
        cin >> first;
        string last;
        cout << "Enter Last Name: ";
        cin >> last;
        string title;
        cout << "Enter Professor's title: ";
        cin >> title;
        controller.addProfessor(ID,first,last,title);
    }

    else if(name == "Show Professors"){
        for (const Professor & el : controller.professors) {
            cout << el << endl;
        }
    }

    else if(name == "Add Student"){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        string first;
        cout << "Enter First Name: ";
        cin >> first;
        string last;
        cout << "Enter Last Name: ";
        cin >> last;
        controller.addStudent(ID, first, last);
    }

    else if(name == "Show Students"){
        for (const Student& el : controller.students)
            cout << el << endl;
    }

    else if(name == "Add Course"){
        string courseName;
        cout << "Enter course name:" ;
        cin  >> courseName;
        string professorLastName;
        cout << "Enter Professor's last name: ";
        cin  >> professorLastName;
        string semester;
        cout << "Enter Semester: ";
        cin >> semester;
        string preCourse;
        vector<string> preCourses;
        while (true){
            cin >> preCourse;
            if (!preCourse.empty()) {
                preCourses.push_back(preCourse);
            }
            else {
                break;
            }
        }
        controller.addCourse(courseName,professorLastName,semester,preCourses);
    }

    else if(name == "Show All Courses"){
        for (const Course& el : controller.courses) {
            cout << el << endl;
        }
    }

    else{
        throw invalid_argument("This Menu hase not been defined!!");
    }
     */

}
