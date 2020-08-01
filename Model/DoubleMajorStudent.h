//
// Created by mehrad on ۲۰۲۰/۷/۲۰.
//

#ifndef TA_19_DOUBLEMAJORSTUDENT_H
#define TA_19_DOUBLEMAJORSTUDENT_H
#include "Student.h"

class DoubleMajorStudent : public  Student {
private:
    std::string major2;
public:
    void setMajor2(const std::string &major2);

public:
    DoubleMajorStudent(const std::string &studentId, const std::string &first, const std::string &last,
                       double workHours, const std::vector<std::string> &passedCourses,
                       const std::map<std::string, double> &currentSemesterCourses, const std::string &major2);
    double salary() const {return 6500 * getWorkHours();}
    double calculateSalary();
};


#endif //TA_19_DOUBLEMAJORSTUDENT_H
