#pragma once
#include <string>
#include <vector>

using namespace std;
#include "student.h"

class StudentManager {
	vector<shared_ptr<Student>> studentList;
public:
	void addStudent();
	void showStudent(int id);
	void showAllStudent();
};