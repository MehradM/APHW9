#include "Controller.h"
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

Controller::Controller(std::string currentSemester)
   : currentSemester{move(currentSemester)} {}


void Controller:: load(){
    ifstream inputStu("students.txt");
    int studentSize;
    inputStu >> studentSize;
    Student stu;
    for( size_t i{0}; i < studentSize; ++i ){
        inputStu >> stu;
        students.push_back(stu);
    }
    inputStu.close();

    ifstream inputProf("professors.txt");
    int profSize;
    inputProf >> profSize;
    Professor prof;
    for( size_t i{0}; i < profSize; ++i){
        inputProf >> prof;
        professors.push_back(prof);
    }
    inputProf.close();

    ifstream inputCourse("courses.txt");
    int courseSize;
    inputCourse >> courseSize;
    Course crs;
    for( size_t i{0}; i < courseSize; ++i){
        inputCourse >> crs;
        courses.push_back(crs);
        if(crs.semester == currentSemester){
            currentSemesterCourses.push_back(crs);
        }
    }
    inputCourse.close();
}

void Controller::save() const{
    ofstream outputStu("students.txt", ios::out);
    outputStu << students.size() << endl;
    for( auto const& stu : students ){
        outputStu << stu << endl;
    }
    outputStu.close();

    ofstream outputProf("professors.txt");
    outputProf << professors.size() << endl;
    for( const auto& prof : professors ){
        outputProf << prof << endl;
    }
    outputProf.close();

    ofstream outputCourse("courses.txt");
    outputCourse << courses.size() << endl;
    for( auto const& crs : courses ){
        outputCourse << crs << endl;
    }
    outputCourse.close();
}

void Controller:: addStudent(const std::string& ID, std::string first, std::string last){
    if(!inStudents(ID)){
        Student stu{ID, move(first), move(last), 0,
                    vector<string>{}, map<string, double>{}};
        students.push_back(stu);
    }
}

void Controller:: addProfessor(std::string ID, std::string first,
        std::string last, std::string title){
    if(!inProfessors(ID)){
        Professor prof{move(ID), move(first), move(last), 0, move(title)};
        professors.push_back(prof);
    }
}

void Controller:: addCourse(std::string courseName, std::string profLast, std::string semester,
               std::vector<std::string> pre){
    if( !inCourses(courseName) && inProfessorsByLastName(profLast) ){
        Course crs{move(courseName), move(profLast), move(semester), move(pre)};
        courses.push_back(crs);
        if( crs.semester == currentSemester){
            currentSemesterCourses.push_back(crs);
        }
    }

}

bool Controller::inStudents(const std::string& ID) const{
    for( const auto& stu : students ){
        if( stu.studentId == ID){
            return true;
        }
    }
    return false;
}

bool Controller::inProfessors(const std::string& ID) const{
    for( const auto& prof : professors ){
        if( prof.profId == ID){
            return true;
        }
    }
    return false;
}

bool Controller::inCourses(const std::string& courseName) const{
    for( const auto& crs : courses ){
        if( crs.courseName == courseName){
            return true;
        }
    }
    return false;
}

bool Controller:: inProfessorsByLastName(const std::string& last) const{
    for( const auto& prof : professors ){
        if( prof.getLastName() == last){
            return true;
        }
    }
    return false;
}

Student& Controller:: findStudent(const string& ID){
    for( auto& stu : students ){
        if(stu.studentId == ID){
            return stu;
        }
    }
    throw invalid_argument("The Student was not found!!");
}

void Controller:: takeCourse(const std::string& studentID, const std::string& courseName){
    if(inCourses(courseName) && preCoursesPassed(findStudent(studentID),courseName)){
        findStudent(studentID).currentSemesterCourses.insert({courseName, 0});
    }
}

const string &Controller::getCurrentSemester() const {
    return currentSemester;
}

const vector<Student> &Controller::getStudents() const {
    return students;
}

const vector<Professor> &Controller::getProfessors() const {
    return professors;
}

const vector<Course> &Controller::getCourses() const {
    return courses;
}

const vector<Course> &Controller::getCurrentSemesterCourses() const {
    return currentSemesterCourses;
}

vector<Course> Controller::getProfessorCourses(const std::string &id) {
    vector<Course> profCourses;
    string lastName = findProfessor(id).getLastName();
    for_each(courses.begin(),courses.end(),[&profCourses,lastName](const Course& course) {
        if (course.profLastName == lastName) profCourses.push_back(course);
    });
    return profCourses;
}

const map<string,double> &Controller::getStudentCourses(const std::string &id) {
    return findStudent(id).currentSemesterCourses;
}

void Controller::dropCourse(const std::string &studentID, const std::string &courseName) {
    findStudent(studentID).currentSemesterCourses.erase(courseName);
}

double Controller::calcProfSalary(const std::string& id) {
    return findProfessor(id).calculateSalary();
}

double Controller::calcStudentSalary(const std::string& id) {
    return findStudent(id).calculateSalary();
}

Professor &Controller::findProfessor(const std::string& ID) {
    for (Professor & el : professors) {
        if(el.profId == ID) {
            return el;
        }
    }
    throw invalid_argument("Professor not found!");
}

void Controller::submitGrade(const std::string& profID,const std::string& studentID,
        const std::string& course,double grade) {
    auto profLastName = findProfessor(profID).getLastName();
    if(any_of(courses.begin(),courses.end(),[profLastName,course](const Course& c){
        return c.getCourseName() == course && c.getProfLastName() ==  profLastName;})) {
        Student& student = findStudent(studentID);
        if((student.currentSemesterCourses.find(course) != student.currentSemesterCourses.end())) {
            student.currentSemesterCourses[course] = grade;
        }
        else {
            throw invalid_argument("The student doesn't have this course!");
        }
    }
    else {
        throw invalid_argument("This professor is not allowed to set grade of this course!");
    }

}

const Course &Controller::findCourse(const std::string &course) {
    for (const Course& el : courses) {
        if(el.courseName == course) {
            return el;
        }
    }
    throw invalid_argument("Course not found!");
}

bool Controller::preCoursesPassed(const Student &student,const std::string& course) {
    Course theCourse = findCourse(course);
    int count = 0;
    for ( const string & el : theCourse.getPreCourses()) {
        if (none_of(student.passedCourses.begin(),student.passedCourses.end(),[&el](const string& preCourse){
            return el == preCourse;
        })) throw invalid_argument("Pre-courses not passed!");
    }
    return true;
}

void Controller::readMembersFromFile() {
    ifstream file("members.txt");
    char type;
    string id, fName, lName, major2,&title = major2;
    double wh;
    Person * person;
    while (file.good()) {
        file >> type >> id >> fName >> lName ;
        switch (type) {
            case 'P':
                file >> title >> wh;
                person = new Professor(id,fName,lName,wh,title);
                break;
            case 'S':
                file >> wh;
                person = new Student(id,fName,lName,wh,vector<string>(0),
                        {{"Mathematics",0}});
                break;
            case 'D':
                file >> major2 >> wh;
                person = new DoubleMajorStudent(id,fName,lName,wh,vector<string>(0),
                        {{"Mathematics",0}},major2);
                break;
        }
        mathClass.push_back(person);
    }
}

double Controller::calculateTotalSalary() {
    double total = 0;
    for (const Person * person : mathClass) {
        total += person->calculateSalary();
    }
    return total;
}
