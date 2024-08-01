#include <iostream>
#include "StudentManager.h"


StudentManager::StudentManager() {
	studentArtList = {};
	studentSciList = {};
}

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
			studentArtList.push_back(make_shared<StudentArt>(name, subject[input - 1], studentArtList.size() + studentSciList.size() + 1));
		}
		else if (input == 2) {
			studentSciList.push_back(make_shared<StudentSci>(name, subject[input - 1], studentArtList.size() + studentSciList.size() + 1));
		}
		else
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
	}
}

void StudentManager::editStudent(int id) {


	for (auto it : studentArtList) {
		if (it->getId() == id) {
			cout << it->getName() << " �л��� �����ϼ̽��ϴ�." << endl;
			int economics, arts;
			cout << "���� ������ �Է��ϼ��� (���� ���� : " << it->getEconomics() << ") -> " << endl;
			cin >> economics;
			cout << "�̼� ������ �Է��ϼ��� (���� ���� : " << it->getArts() << ") -> " << endl;
			cin >> arts;
			it->setScore(economics, arts);
			break;
		}
	}

	for (auto it : studentSciList) {
		if (it->getId() == id) {
			cout << it->getName() << " �л��� �����ϼ̽��ϴ�." << endl;
			int science, math;
			cout << "���� ������ �Է��ϼ��� (���� ���� : " << it->getScience() << ") -> " << endl;
			cin >> science;
			cout << "���� ������ �Է��ϼ��� (���� ���� : " << it->getMath() << ") -> " << endl;
			cin >> math;
			it->setScore(science, math);
			break;
		}
	}
}



void StudentManager::showStudent(int id) {


	for (auto it : studentSciList) {
		if (it->getId() == id) {
				cout << "���� : " << it->getScience() << endl;
				cout << "���� : " << it->getMath() << endl;
		}
	}

	for (auto it : studentArtList) {
		if (it->getId() == id) {
			cout << "���� : " << it->getEconomics() << endl;
			cout << "�̼� : " << it->getArts() << endl;
		}
	}
}

void StudentManager::showAllStudent() {
	int sciIdx = 0, artIdx = 0;
	int j = studentArtList.size();
	int k = studentSciList.size();

	if (j + k == 0) {
		cout << "��ϵ� �л��� �����ϴ�." << endl;
		return;
	}

	for (int i = 1; i <= j + k; i++) {
		if (artIdx < j && sciIdx < k && studentArtList[artIdx]->getId() > studentSciList[sciIdx]->getId()) {
			cout << studentArtList[artIdx]->getName() << " �л�, �й�: " << studentArtList[artIdx]->getId() << ", ";
			cout << "����" << endl;
			cout << "���� : " << studentArtList[artIdx]->getEconomics() << endl;
			cout << "�̼� : " << studentArtList[artIdx]->getArts() << endl;
			cout << "���� : " << studentArtList[artIdx]->getavgScore() << endl;
			artIdx++;
		}
		else if (sciIdx < k) {
			cout << studentSciList[artIdx]->getName() << " �л�, �й�: " << studentSciList[artIdx]->getId() << ", ";
			cout << "�̰�" << endl;
			cout << "���� : " << studentSciList[sciIdx]->getScience() << endl;
			cout << "���� : " << studentSciList[sciIdx]->getMath() << endl;
			cout << "���� : " << studentSciList[artIdx]->getavgScore() << endl;
			sciIdx++;
		}
		else {
			cout << studentArtList[artIdx]->getName() << " �л�, �й�: " << studentArtList[artIdx]->getId() << ", ";
			cout << "����" << endl;
			cout << "���� : " << studentArtList[artIdx]->getEconomics() << endl;
			cout << "�̼� : " << studentArtList[artIdx]->getArts() << endl;
			cout << "���� : " << studentArtList[artIdx]->getavgScore() << endl;
			artIdx++;
		}
	}
}