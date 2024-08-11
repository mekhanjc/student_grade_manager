#ifndef STUDENTART_H
#define STUDENTART_H

#include "student.h"

class StudentArt : public Student {

    QMap<QString, int> ArtSubjectList;

public:
    StudentArt();
    StudentArt(QString name, QString subject, QString id, QString gender,\
               QString birthday, QString phone, QString address);
    void setScore(QString subject, int score);
};

#endif // STUDENTART_H
