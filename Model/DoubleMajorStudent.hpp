//
// Created by mehrad on ۲۰۲۰/۷/۲۰.
//

#ifndef TA_19_DOUBLEMAJORSTUDENT_HPP
#define TA_19_DOUBLEMAJORSTUDENT_HPP
#include "Student.h"

class DoubleMajorStudent : virtual public  Student {
private:
    std::string major2;
public:
    void setMajor2(const std::string &major2);

public:
    DoubleMajorStudent(const std::string &studentId, const std::string &first, const std::string &last,
                       double workHours, const std::vector<std::string> &passedCourses,
                       const std::map<std::string, double> &currentSemesterCourses, const std::string &major2);

    virtual double calculateSalary() final;
};


#endif //TA_19_DOUBLEMAJORSTUDENT_HPP
