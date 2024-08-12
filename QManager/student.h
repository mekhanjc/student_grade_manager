#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <memory>
#include <QString>
#include <QMap>

using namespace std;

class Student {
    QString name;
    QString subject;
    QString gender;
    QString birthday;
    QString phonenumber;
    QString address;

    int id;
    double avgScore = 0;

public:
    Student() {this->name = ""; this->id = 0; this->subject = ""; this->gender = "";
            this->birthday = ""; this->phonenumber = ""; this->address = "";}
    Student(QString name, QString subject, int id, QString gender,\
            QString birthday, QString phonenumber, QString address);
    QString getName();
    void setName(QString name);
    QString getSubject();
    void setSubject(QString subject);
    void setId(int id);
    int getId();
    void setGender(QString);
    QString getGender();
    void setBirthday(QString);
    QString getBirthday();
    void setPhoneNumber(QString);
    QString getPhoneNumber();
    void setAddress(QString);
    QString getAddress();
    void setavgScore(double avgScore);
    double getavgScore();

};

#endif // STUDENT_H
