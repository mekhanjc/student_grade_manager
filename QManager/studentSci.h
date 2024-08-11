#ifndef STUDENTSCI_H
#define STUDENTSCI_H

#include "student.h"

class StudentSci : public Student {

    QMap<QString, int> SciSubjectList;

public:
    StudentSci();
    StudentSci(QString name, QString subject, QString id, QString gender,\
               QString birthday, QString phone, QString address);
    void setScore(QString subject, int score);
};


#endif // STUDENTSCI_H
