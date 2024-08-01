#include <iostream>
#include <fstream>
#include "StudentManager.h"


void StudentManager::showMenu() {
	int num, id;
	cout << "------------------------------" << endl;
	cout << "밑의 실행 목록중 선택해주세요." << endl;
	cout << "------------------------------" << endl;
	cout << "1.학생등록 2.성적조회 3.전체성적조회 4.성적입력 5.성적표출력 6.종료" << endl;
	cin >> num;
	switch (num) {
	case 1:
		addStudent();
		break;
	case 2:
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
		cout << "학번 ID 입력 : ";
		cin >> id;
		editStudent(id);
		break;
	case 5:
		cout << "성적표를 출력합니다." << endl;
		cout << "학번 ID 입력 : ";
		cin >> id;
		printStudent(id);
		break;
	case 6:
		cout << "프로그램 종료합니다." << endl;
		exit(0);
		break;
	default:
		cout << "잘못 선택 하셨습니다. 프로그램 종료합니다." << endl;
		exit(0);
	}
}
StudentManager::StudentManager() {
	studentArtList = {};
	studentSciList = {};
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
		if (input == 1) {
			cout << "이름을 입력하세요 : ";
			cin >> name;
			studentArtList.push_back(make_shared<StudentArt>(name, subject[input - 1], studentArtList.size() + studentSciList.size() + 1));
		}
		else if (input == 2) {
			cout << "이름을 입력하세요 : ";
			cin >> name;
			studentSciList.push_back(make_shared<StudentSci>(name, subject[input - 1], studentArtList.size() + studentSciList.size() + 1));
		}
		else {
			cout << "잘못 선택 하셨습니다. 프로그램 종료합니다." << endl;
			exit(0);
			break;
		}
	}
}


void StudentManager::editStudent(int id) {


	for (auto it : studentArtList) {
		if (it->getId() == id) {
			cout << it->getName() << " 학생의 성적입니다." << endl;
			int economics, arts;
			cout << "경제 성적을 입력하세요 (현재 성적 : " << it->getEconomics() << ") -> " << endl;
			cin >> economics;
			cout << "미술 성적을 입력하세요 (현재 성적 : " << it->getArts() << ") -> " << endl;
			cin >> arts;
			it->setScore(economics, arts);
			break;
		}
	}

	for (auto it : studentSciList) {
		if (it->getId() == id) {
			cout << it->getName() << " 학생의 성적입니다." << endl;
			int science, math;
			cout << "과학 성적을 입력하세요 (현재 성적 : " << it->getScience() << ") -> " << endl;
			cin >> science;
			cout << "수학 성적을 입력하세요 (현재 성적 : " << it->getMath() << ") -> " << endl;
			cin >> math;
			it->setScore(science, math);
			break;
		}
	}
}



void StudentManager::showStudent(int id) {


	for (auto it : studentSciList) {
		if (it->getId() == id) {
			if (it->getScience() < 0 || it->getMath() < 0) {
				cout << "입력된 성적이 없습니다." << endl;
				return;
			}
			cout << "과학 성적 : " << it->getScience() << endl;
			cout << "수학 성적 : " << it->getMath() << endl;
			cout << "평균 성적 : " << it->getavgScore() << endl;
		}
	}

	for (auto it : studentArtList) {
		if (it->getId() == id) {
			if (it->getEconomics() < 0 || it->getArts() < 0) {
				cout << "입력된 성적이 없습니다." << endl;
				return;
			}
			cout << "경제 성적 : " << it->getEconomics() << endl;
			cout << "미술 성적 : " << it->getArts() << endl;
			cout << "평균 성적 : " << it->getavgScore() << endl;
		}

	}
}

void StudentManager::showAllStudent() {
	int j = studentArtList.size();
	int k = studentSciList.size();

	if (j + k == 0) {
		cout << "등록된 학생이 없습니다." << endl;
		return;
	}

	for (int artIdx = 0; artIdx < j; artIdx++) {
		cout << studentArtList[artIdx]->getName() << " 학생, 학번: " << studentArtList[artIdx]->getId() << ", ";
		cout << "문과입니다." << endl;
		if (studentArtList[artIdx]->getEconomics() < 0 || studentArtList[artIdx]->getArts() < 0) {
			cout << "입력된 성적이 없습니다." << endl;
			continue;
		}
		cout << "경제 : " << studentArtList[artIdx]->getEconomics() << endl;
		cout << "미술 : " << studentArtList[artIdx]->getArts() << endl;
		cout << "평균 : " << studentArtList[artIdx]->getavgScore() << endl;
	}

	for (int sciIdx = 0; sciIdx < k; sciIdx++) {
		cout << studentSciList[sciIdx]->getName() << " 학생, 학번: " << studentSciList[sciIdx]->getId() << ", ";
		cout << "이과입니다." << endl;
		if (studentSciList[sciIdx]->getScience() < 0 || studentSciList[sciIdx]->getMath() < 0) {
			cout << "입력된 성적이 없습니다." << endl;
			continue;
		}
		cout << "과학 : " << studentSciList[sciIdx]->getScience() << endl;
		cout << "수학 : " << studentSciList[sciIdx]->getMath() << endl;
		cout << "평균 : " << studentSciList[sciIdx]->getavgScore() << endl;
	}
}

void StudentManager::printStudent(int id) {
	ofstream fout("c:\\temp\\student.txt");

	if (!fout) {
		cout << "파일을 열 수 없습니다." << endl;
		return;
	}

	for (auto it : studentSciList) {
		if (it->getId() == id) {
			if (it->getScience() < 0 || it->getMath() < 0) {
				cout << "입력된 성적이 없습니다." << endl;
				return;
			}
			fout << "과학 성적 : " << it->getScience() << endl;
			fout << "수학 성적 : " << it->getMath() << endl;
			fout << "평균 성적 : " << it->getavgScore() << endl;
		}
	}
	
	for (auto it : studentArtList) {
		if (it->getId() == id) {
			if (it->getEconomics() < 0 || it->getArts() < 0) {
				cout << "입력된 성적이 없습니다." << endl;
				return;
			}
			fout << "경제 성적 : " << it->getEconomics() << endl;
			fout << "미술 성적 : " << it->getArts() << endl;
			fout << "평균 성적 : " << it->getavgScore() << endl;
		}
	}
	cout << "출력이 완료되었습니다." << endl;
}