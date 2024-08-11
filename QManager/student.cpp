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
void Student::setPhoneNumber(QString phonenumber){
    this->phonenumber = phonenumber;
}
QString Student::getPhoneNumber(){
    return phonenumber;
}
void Student::setAddress(QString address){
    this->address = address;
}
QString Student::getAddress(){
    return address;
}
double Student::getavgScore() {
    return avgScore;
}
void Student::setavgScore(double avgScore) {
    this->avgScore = avgScore;
}
void Student::setScore(int, int) {

}
