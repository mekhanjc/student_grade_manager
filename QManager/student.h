#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <QString>
#include <QMap>

using namespace std;

class Student {
    QString name;
    QString subject;
    QString gender;
    QString birthday;
    QString phone;
    QString address;

    QString id;
    double avgScore = 0;

public:
    Student() {this->name = ""; this->id = 0; this->subject = ""; this->gender = "";
            this->birthday = ""; this->phone = ""; this->address = "";}
    Student(QString name, QString subject, QString id, QString gender,\
            QString birthday, QString phone, QString address);
    QString getName();
    void setName(QString name);
    QString getSubject();
    void setSubject(QString subject);
    void setId(QString id);
    QString getId();
    void setavgScore(double avgScore);
    double getavgScore();
    void setGender(QString gender);
    QString getGender();
    void setBirthday(QString birthday);
    QString getBirthday();
    void setPhone(QString phone);
    QString getPhone();
    void setAddress(QString address);
    QString getAddress();

};

#endif // STUDENT_H
