#include <iostream>
#include "StudentManager.h"

void StudentManager::showMenu() {
	int num;
	cout << "밑의 실행 목록중 선택해주세요." << endl;
	cout << "------------------------------" << endl;
	cout << "1.학생등록 2.성적조회 3.전체성적조회 4.성적입력 5.성적수정 6.성적삭제 7.종료" << endl;
	cin >> num;
	switch (num) {
	case 1:
		addStudent();
		break;
	case 2:
		int id;
		cout << "학번 ID 입력 : ";
		cin >> id;
		showStudent(id);
		break;
	case 3:
		cout << "전체 성적 조회합니다." << endl;
		showAllStudent();
		break;
	case 4:
		cout << "성적을 입력합니다. " << endl;
		break;
	case 5:
		cout << "성적을 수정합니다. " << endl;
	case 6:
		cout << "성적을 삭제합니다. " << endl;
		break;
	case 7:
		cout << "프로그램 종료합니다." << endl;
		break;
	default:
		cout << "잘못 선택 하셨습니다. 프로그램 종료합니다." << endl;
		
	}
}

void StudentManager::addStudent() {

	int input;
	string subject[2] = { "문과", "이과" };

	while (true) {
		cout << "학생을 등록합니다 -> 1.학생 등록  2.종료  3.초기메뉴  : ";
		cin >> input;
		if (input == 2) {
			cout << "종료합니다." << endl;
			break;
		}
		else if (input > 3) {
			cout << "잘못 입력하셨습니다." << endl;
			continue;
		}
		else if (input == 3) {
			showMenu();
			break;
		}

		string name;
		
		
		cout << "문/이과를 선택하세요. -> 1.문과  2.이과   : ";
		cin >> input;
		cout << "이름을 입력하세요 : ";
		cin >> name;

		if (input == 1) {
			studentList.push_back(make_shared<Student>(name, subject[input - 1], this->studentList.size() + 1));
		}
		if (input == 2) {
			studentList.push_back(make_shared<Student>(name, subject[input - 1], this->studentList.size() + 1));
		}
		else {
			cout << "잘못 입력하셨습니다." << endl;
			showMenu();
		}
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
		}
		else {
			cout << "등록된 학생이 없습니다. " << endl;
			cout << "초기메뉴로 돌아갑니다. " << endl;
			showMenu();
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
