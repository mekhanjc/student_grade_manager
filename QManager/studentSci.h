#ifndef STUDENTSCI_H
#define STUDENTSCI_H

#include "student.h"

class StudentSci : public Student {
    int science;
    int math;
public:
    StudentSci();
    StudentSci(string name, string subject, int id);
    void setScore(int science, int math);
    int getScience() const;
    int getMath() const;

};


#endif // STUDENTSCI_H
