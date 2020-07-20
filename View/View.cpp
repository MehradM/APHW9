#include <stdexcept>
#include <iomanip>
#include "View.h"

using namespace std;

View::View(Controller controller)
   : controller{move(controller)} {}

void View::makeMenus( Menu* root ){
    // make main Menu
    auto commandsFromFile = new CommandsFromFileMenu{"Commands From File", root};
    auto studentMenu = new InternalMenu{"Student Menu", root};
    auto professorMenu = new InternalMenu{"Professor Menu", root};
    auto managerMenu = new InternalMenu{"Manager Menu", root};
    auto mathClass = new InternalMenu("Math Class",root);
    root->setSubMenus(vector<Menu*>
            {commandsFromFile, studentMenu, professorMenu, managerMenu,mathClass});

    // make Student Menu

    auto showThisSemesterCourses = new LeafMenu{"Show This Semester Courses", studentMenu,[](Controller& cont){
        for (const Course& course : cont.getCurrentSemesterCourses()) {
            cout << course << endl;
        }
    }};
    auto takeCourse = new LeafMenu{"Take Course", studentMenu,[](Controller& cont){
        string ID;
        cout << "Enter student ID: ";
        cin >> ID;
        string course;
        cout << "Enter course name: ";
        cin >> course;
        cont.takeCourse(ID,course);
    }};

    auto dropCourse = new LeafMenu{"Drop Course", studentMenu,[](Controller& cont){
        string ID;
        cout << "Enter student ID: ";
        cin >> ID;
        string course;
        cout << "Enter course name: ";
        cin >> course;
        cont.dropCourse(ID,course);
    }};

    auto showMyCourses = new LeafMenu{"Show Student Courses In Current Semester", studentMenu,[](Controller& cont){
        string ID;
        cout << "Enter student ID:";
        cin >> ID;
        for (const pair<string,double> student : cont.getStudentCourses(ID)) {
            cout << "Course:" << student.first << "\tGrade:" << student.second << endl;
        }
    }};

    auto calculateMySalary = new LeafMenu{"Calculate Student Salary", studentMenu,[](Controller& cont){
        string ID;
        cout << "Enter student ID:";
        cin >> ID;
        cout << "Your Salary:" << cont.calcStudentSalary(ID);
    }};

    studentMenu->setSubMenus(vector<Menu*>
              {showThisSemesterCourses, takeCourse, dropCourse, showMyCourses, calculateMySalary});

    // make Professor Menu
    auto showMyCoursesInThisSemester =
            new LeafMenu{"Show Professor Courses In Current Semester", professorMenu,[](Controller& cont){
                string ID;
                cout << "Enter professor ID:";
                cin >> ID;
                vector<Course> courses = cont.getProfessorCourses(ID);
                for (const Course& el : courses) {
                    cout << el << endl;
                }
            }};

    auto submitGrade = new LeafMenu{"Submit Grade", professorMenu,[](Controller& cont){
        string professorID;
        cout << "Enter professor ID:";
        cin >> professorID;
        string studentID;
        cout << "Enter student ID: ";
        cin >> studentID;
        string course;
        cout << "Enter course name: ";
        cin >> course;
        double grade;
        cout << "Enter Grade:";
        cin >> grade;
        cont.submitGrade(professorID,studentID,course,grade);
    }};

    auto profCalculateMySalary = new LeafMenu{"Calculate Professor Salary", professorMenu,[](Controller& cont){
        string ID;
        cout << "Enter professor ID:";
        cin >> ID;
        cout << "Your salary: " << cont.calcProfSalary(ID);
    }};

    professorMenu->setSubMenus(vector<Menu*>
                       {showMyCoursesInThisSemester, submitGrade, profCalculateMySalary});

    // make Manger Menu

    auto peopleMenu = new InternalMenu{"People", managerMenu};
    auto coursesMenu = new InternalMenu{"Courses", managerMenu};
    managerMenu->setSubMenus( vector<Menu*> {peopleMenu, coursesMenu});

    // make People Menu
    auto addProfessor = new LeafMenu{"Add Professor", peopleMenu,[](Controller& cont){
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
        cont.addProfessor(ID,first,last,title);
    }};

    auto showProfessors = new LeafMenu{"Show Professors", peopleMenu,[](Controller& cont){
        for (const Professor& el : cont.getProfessors())
            cout << el << endl;
    }};

    auto addStudent = new LeafMenu{"Add Student", peopleMenu,[](Controller& cont){
        string ID;
        cout << "Enter student number: ";
        cin >> ID;
        string first;
        cout << "Enter First Name: ";
        cin >> first;
        string last;
        cout << "Enter Last Name: ";
        cin >> last;
        cont.addStudent(ID, first, last);
    }};

    auto showStudents = new LeafMenu{"Show Students", peopleMenu,[](Controller& cont){
        for (const Student& el : cont.getStudents())
            cout << el << endl;
    }};

    peopleMenu->setSubMenus(vector<Menu*>
                                    {addProfessor, showProfessors, addStudent, showStudents});


    // make Courses Menu
    auto addCourses = new LeafMenu{"Add Course", coursesMenu,[](Controller& cont){
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
            if (preCourse != "-") {
                preCourses.push_back(preCourse);
            }
            else {
                break;
            }
            preCourse = "";
        }
        cont.addCourse(courseName,professorLastName,semester,preCourses);
    }};

    auto managerShowThisSemesterCourses =
            new LeafMenu{"Show Current Semester Courses", coursesMenu,[](Controller& cont){
                for (const Course& el : cont.getCurrentSemesterCourses()) {
                    cout << el << endl;
                }
            }};

    auto showAllCourses = new LeafMenu{"Show All Courses", coursesMenu,[](Controller& cont){
        for (const Course& el : cont.getCourses()) {
            cout << el << endl;
        }
    }};
    coursesMenu->setSubMenus(vector<Menu*>
            {addCourses, managerShowThisSemesterCourses, showAllCourses});

    auto readMembers = new LeafMenu("Read Members", mathClass,[](Controller& cont){cont.readMembersFromFile();});
    auto calculateTotalSalary = new LeafMenu("Calculate Total Salary",mathClass,[](Controller& cont){
        cout << fixed << "Total Salary of MathClass: " << setprecision(2) << cont.calculateTotalSalary() << endl;
    });

    mathClass->setSubMenus(vector<Menu*> {readMembers,calculateTotalSalary});


}

void View::exec(){
    try {
        controller.load();
        Menu::setController(controller);
        Menu *mainMenu = new InternalMenu{"Main Menu", nullptr};
        makeMenus(mainMenu);
        Menu::setCurrentMenu(mainMenu);

        while (true) {
            try {
                Menu::getCurrentMenu()->showSubMenus();
                Menu::getCurrentMenu()->run();
            }
            catch( const invalid_argument& e){
                cout << e.what() << endl;
            }
        }
    }

    catch( const invalid_argument& e){
        cout << e.what() << endl;
    }
}


