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
StudentSci::StudentSci() {
	this->science = -1;
	this->math = -1;
}
StudentSci::StudentSci(string name, string subject, int id) {
	setName(name);
	setSubject(subject);
	setId(id);
	this->science = -1;
	this->math = -1;
}
StudentArt::StudentArt() {
	this->economics = -1;
	this->arts = -1;
}
StudentArt::StudentArt(string name, string subject, int id) {
	setName(name);
	setSubject(subject);
	setId(id);
	this->economics = -1;
	this->arts = -1;
}
void StudentSci::setScore(int science, int math) {
	this->science = science;
	this->math = math;
	setavgScore((double)(science + math) / 2);
}
void StudentArt::setScore(int economics, int arts) {
	this->economics = economics;
	this->arts = arts;
	setavgScore((double)(economics + arts) / 2);
}
int StudentSci::getScience() const {
	return science;
}
int StudentSci::getMath() const  {
	return math;
}
int StudentArt::getEconomics() const {
	return economics;
}
int StudentArt::getArts() const {
	return arts;
}