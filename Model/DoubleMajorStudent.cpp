//
// Created by mehrad on ۲۰۲۰/۷/۲۰.
//

#include "DoubleMajorStudent.h"



DoubleMajorStudent::DoubleMajorStudent(const std::string &studentId, const std::string &first, const std::string &last,
                                       double workHours, const std::vector<std::string> &passedCourses,
                                       const std::map<std::string, double> &currentSemesterCourses,
                                       const std::string &major2) : Student(studentId, first, last, workHours,
                                                                            passedCourses, currentSemesterCourses),
                                                                    major2(major2) {}

void DoubleMajorStudent::setMajor2(const std::string &major2) {
    DoubleMajorStudent::major2 = major2;
}

double DoubleMajorStudent::calculateSalary() {
    return 6500 * getWorkHours();
}