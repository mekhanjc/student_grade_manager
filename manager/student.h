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

class StudentSci : public Student {
	int science;
	int math;
public:
	StudentSci(string name, string subject, int id);
	void setScore(int science, int math);
	int getScience();
	int getMath();

};

class StudentArt : public Student {
	int economics;
	int arts;
public:
	StudentArt(string name, string subject, int id);
	void setScore(int economics, int arts);
	int getEconomics();
	int getArts();

};