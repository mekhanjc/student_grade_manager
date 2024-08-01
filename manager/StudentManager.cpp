#include <iostream>
#include "StudentManager.h"

void StudentManager::showMenu() {
	int num;
	cout << "���� ���� ����� �������ּ���." << endl;
	cout << "------------------------------" << endl;
	cout << "1.�л���� 2.������ȸ 3.��ü������ȸ 4.�����Է� 5.�������� 6.�������� 7.����" << endl;
	cin >> num;
	switch (num) {
	case 1:
		addStudent();
		break;
	case 2:
		int id;
		cout << "�й� ID �Է� : ";
		cin >> id;
		showStudent(id);
		break;
	case 3:
		cout << "��ü ���� ��ȸ�մϴ�." << endl;
		showAllStudent();
		break;
	case 4:
		cout << "������ �Է��մϴ�. " << endl;
		break;
	case 5:
		cout << "������ �����մϴ�. " << endl;
	case 6:
		cout << "������ �����մϴ�. " << endl;
		break;
	case 7:
		cout << "���α׷� �����մϴ�." << endl;
		break;
	default:
		cout << "�߸� ���� �ϼ̽��ϴ�. ���α׷� �����մϴ�." << endl;
		
	}
}

void StudentManager::addStudent() {

	int input;
	string subject[2] = { "����", "�̰�" };

	while (true) {
		cout << "�л��� ����մϴ� -> 1.�л� ���  2.����  3.�ʱ�޴�  : ";
		cin >> input;
		if (input == 2) {
			cout << "�����մϴ�." << endl;
			break;
		}
		else if (input > 3) {
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
			continue;
		}
		else if (input == 3) {
			showMenu();
			break;
		}

		string name;
		
		
		cout << "��/�̰��� �����ϼ���. -> 1.����  2.�̰�   : ";
		cin >> input;
		cout << "�̸��� �Է��ϼ��� : ";
		cin >> name;

		if (input == 1) {
			studentList.push_back(make_shared<Student>(name, subject[input - 1], this->studentList.size() + 1));
		}
		if (input == 2) {
			studentList.push_back(make_shared<Student>(name, subject[input - 1], this->studentList.size() + 1));
		}
		else {
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
			showMenu();
		}
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
		}
		else {
			cout << "��ϵ� �л��� �����ϴ�. " << endl;
			cout << "�ʱ�޴��� ���ư��ϴ�. " << endl;
			showMenu();
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
