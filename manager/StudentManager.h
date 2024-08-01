#pragma once
#include <string>
#include <vector>

using namespace std;
#include "student.h"

class StudentManager {
	vector<shared_ptr<StudentArt>> studentArtList;
	vector<shared_ptr<StudentSci>> studentSciList;
public:
	void showMenu();
	StudentManager();
	void addStudent();
	void editStudent(int id);
	void showStudent(int id);
	void showAllStudent();
	void showMenu();
};