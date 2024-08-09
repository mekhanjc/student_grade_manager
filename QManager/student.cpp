#include "student.h"


Student::Student(QString name, QString subject, int id, QString gender,
        QString birthday, QString phonenumber, QString address) {
    this->name = name;
    this->subject = subject;
    this->id = id;
    this->gender = gender;
    this->birthday = birthday;
    this->phonenumber = phonenumber;
    this->address = address;
}
QString Student::getName() {
    return name;
}
void Student::setName(QString name) {
    this->name = name;
}
QString Student::getSubject() {
    return subject;
}
void Student::setSubject(QString subject) {
    this->subject = subject;
}
void Student::setId(int id) {
    this->id = id;
}
int Student::getId() {
    return id;
}
double Student::getavgScore() {
    return avgScore;
}
void Student::setavgScore(double avgScore) {
    this->avgScore = avgScore;
}
void Student::setScore(int, int) {

}
