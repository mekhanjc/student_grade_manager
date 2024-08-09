#include "student.h"

Student::Student(string name, string subject, int id) {
    this->name = name;
    this->subject = subject;
    this->id = id;
}
string Student::getName() {
    return name;
}
void Student::setName(string name) {
    this->name = name;
}
string Student::getSubject() {
    return subject;
}
void Student::setSubject(string subject) {
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
