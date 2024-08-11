#include "student.h"


Student::Student(QString name, QString subject, int id, QString gender,
        QString birthday, QString phone, QString address) {
    this->name = name;
    this->subject = subject;
    this->id = id;
    this->gender = gender;
    this->birthday = birthday;
    this->phone = phone;
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

void Student::setGender(QString gender){
    this->gender = gender;
}

QString Student::getGender(){
    return gender;
}

void Student::setBirthday(QString birthday){
    this->birthday = birthday;
}

QString Student::getBirthday(){
    return birthday;
}

void Student::setPhone(QString phone){
    this->phone = phone;
}

QString Student::getPhone(){
    return phone;
}

void Student::setAddress(QString address){
    this->address = address;
}

QString Student::getAddress(){
    return address;
}
