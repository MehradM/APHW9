#ifndef TA_19_CONTROLLER_H
#define TA_19_CONTROLLER_H

#include <string>
#include <vector>
#include "../Model/Student.h"
#include "../Model/Professor.h"
#include "../Model/Course.h"
#include "../Model/DoubleMajorStudent.hpp"

class Controller {
    friend class Menu;
    friend class CommandsFromFileMenu;
    friend class LeafMenu;
private:
    std::string currentSemester = "98-99";
    std::vector<Student> students;
    std::vector<Professor> professors;
    std::vector<Course> courses;
    std::vector<Course> currentSemesterCourses;
    std::vector<Person*> mathClass;
public:
    const std::string &getCurrentSemester() const;

    const std::vector<Student> &getStudents() const;

    const std::vector<Professor> &getProfessors() const;

    const std::vector<Course> &getCourses() const;

    const std::vector<Course> &getCurrentSemesterCourses() const;

    std::vector<Course> getProfessorCourses(const std::string& id);

    const std::map<std::string,double> &getStudentCourses (const std::string& id);

private:
    Controller() = default;

public:
    explicit Controller(std::string currentSemester);
    void load();
    void save() const;

    void addStudent(const std::string& ID, std::string first, std::string last);
    void addProfessor(std::string ID, std::string first, std::string last, std::string title);
    void addCourse(std::string courseName, std::string profLast, std::string semester,
            std::vector<std::string> pre);
    void takeCourse(const std::string& studentID, const std::string& courseName);
    Student& findStudent(const std::string& ID);
    Professor& findProfessor(const std::string& ID);
    const Course& findCourse(const std::string& profID);
    void dropCourse(const std::string& studentID, const std::string& courseName);
    void setWorkHours(const std::string& ID, double wh);

    bool inStudents(const std::string& ID) const;
    bool inProfessors(const std::string& ID) const;
    bool inProfessorsByLastName(const std::string& last) const;
    bool inCourses(const std::string& courseName) const;


    double calcProfSalary(const std::string& ID);
    double calcStudentSalary(const std::string& ID);

    void submitGrade(const std::string& profID,const std::string& studentID,const std::string& course,double grade);

    bool preCoursesPassed(const Student& a, const std::string& course);

    void readMembersFromFile();
    double calculateTotalSalary();
};


#endif //TA_19_CONTROLLER_H
