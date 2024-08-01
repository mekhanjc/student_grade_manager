#include <iostream>
#include "StudentManager.h"

void StudentManager::addStudent() {

	int input;
	string subject[2] = { "문과", "이과" };

	while (true) {
		cout << "학생을 등록합니다 -> 1.학생 등록  2.종료" << endl;
		cin >> input;
		if (input == 2)
			break;
		else if (input != 1) {
			cout << "잘못 입력하셨습니다." << endl;
			continue;
		}

		string name;
		
		
		cout << "문/이과를 선택하세요. -> 1.문과  2.이과" << endl;
		cin >> input;
		cout << "이름을 입력하세요 : ";
		cin >> name;

		if (input == 1) {
			studentList.push_back(make_shared<Student>(name, subject[input - 1], this->studentList.size() + 1));
		}
		if (input == 2) {
			studentList.push_back(make_shared<Student>(name, subject[input - 1], this->studentList.size() + 1));
		}
		else
			cout << "잘못 입력하셨습니다." << endl;
	}



}

void StudentManager::showStudent(int id) {
	for (auto it : studentList) {
		if (it->getId() == id) {
			if (it->getSubject() == "이과") {
				auto studentSci = dynamic_cast<StudentSci*>(it.get());
				if (studentSci) {
					cout << "과학 : " << studentSci->getScience() << endl;
					cout << "수학 : " << studentSci->getMath() << endl;
				}
			}
			else {
				auto studentArt = dynamic_cast<StudentArt*>(it.get());
				if (studentArt) {
					cout << "경제 : " << studentArt->getEconomics() << endl;
					cout << "미술 : " << studentArt->getArts() << endl;
				}
			}
			break;
		}
	}
}

void StudentManager::showAllStudent() {
	for (auto it : studentList) {
		if (it->getSubject() == "이과") {
			auto studentSci = dynamic_cast<StudentSci*>(it.get());
			if (studentSci) {
				cout << "과학 : " << studentSci->getScience() << endl;
				cout << "수학 : " << studentSci->getMath() << endl;
			}
		}
		else {
			auto studentArt = dynamic_cast<StudentArt*>(it.get());
			if (studentArt) {
				cout << "경제 : " << studentArt->getEconomics() << endl;
				cout << "미술 : " << studentArt->getArts() << endl;
			}
		}
	}
}
