#include <iostream>
#include "StudentManager.h"

void StudentManager::addStudent() {

	int input;
	string subject[2] = { "����", "�̰�" };

	while (true) {
		cout << "�л��� ����մϴ� -> 1.�л� ���  2.����" << endl;
		cin >> input;
		if (input == 2)
			break;
		else if (input != 1) {
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
			continue;
		}

		string name;
		
		
		cout << "��/�̰��� �����ϼ���. -> 1.����  2.�̰�" << endl;
		cin >> input;
		cout << "�̸��� �Է��ϼ��� : ";
		cin >> name;

		if (input == 1) {
			studentList.push_back(make_shared<Student>(name, subject[input - 1], this->studentList.size() + 1));
		}
		if (input == 2) {
			studentList.push_back(make_shared<Student>(name, subject[input - 1], this->studentList.size() + 1));
		}
		else
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
	}



}

void StudentManager::showStudent(int id) {
	for (auto it : studentList) {
		if (it->getId() == id) {
			if (it->getSubject() == "�̰�") {
				auto studentSci = dynamic_cast<StudentSci*>(it.get());
				if (studentSci) {
					cout << "���� : " << studentSci->getScience() << endl;
					cout << "���� : " << studentSci->getMath() << endl;
				}
			}
			else {
				auto studentArt = dynamic_cast<StudentArt*>(it.get());
				if (studentArt) {
					cout << "���� : " << studentArt->getEconomics() << endl;
					cout << "�̼� : " << studentArt->getArts() << endl;
				}
			}
			break;
		}
	}
}

void StudentManager::showAllStudent() {
	for (auto it : studentList) {
		if (it->getSubject() == "�̰�") {
			auto studentSci = dynamic_cast<StudentSci*>(it.get());
			if (studentSci) {
				cout << "���� : " << studentSci->getScience() << endl;
				cout << "���� : " << studentSci->getMath() << endl;
			}
		}
		else {
			auto studentArt = dynamic_cast<StudentArt*>(it.get());
			if (studentArt) {
				cout << "���� : " << studentArt->getEconomics() << endl;
				cout << "�̼� : " << studentArt->getArts() << endl;
			}
		}
	}
}
