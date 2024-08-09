#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Student {
    string name;
    string subject;
    int id;
    double avgScore = 0;
public:
    Student() {this->name = ""; this->id = 0; this->subject = ""; }
    Student(string name, string subject, int id);
    string getName();
    void setName(string name);
    string getSubject();
    void setSubject(string subject);
    void setId(int id);
    int getId();
    void setavgScore(double avgScore);
    double getavgScore();
    virtual void setScore(int, int);
};

#endif // STUDENT_H
