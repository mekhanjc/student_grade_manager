#ifndef STUDENTSCI_H
#define STUDENTSCI_H

#include "student.h"

class StudentSci : public Student {

    QMap<QString, int> SciSubjectList;

public:
    StudentSci();
    StudentSci(QString name, QString subject, int id, QString gender,\
               QString birthday, QString phonenumber, QString address);
    void setScore(QString subject, int score);
    int getScience() const;
    int getMath() const;

};


#endif // STUDENTSCI_H
