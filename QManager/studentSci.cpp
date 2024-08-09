#include "studentSci.h"

StudentSci::StudentSci() {

}

StudentSci::StudentSci(QString name, QString subject, int id) {
    setName(name);
    setSubject(subject);
    setId(id);

}

void StudentSci::setScore(QString subject,int score) {

    this->SciSubjectList[subject] = score;
}

int StudentSci::getScience() const {

}

int StudentSci::getMath() const  {

}
