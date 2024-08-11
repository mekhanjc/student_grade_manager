#include "studentSci.h"

StudentSci::StudentSci() {

}

StudentSci::StudentSci(QString name, QString subject, int id, QString gender,
                       QString birthday, QString phonenumber, QString address) {
    setName(name);
    setSubject(subject);
    setId(id);

}

void StudentSci::setScore(QString subject,int score) {

    this->SciSubjectList[subject] = score;
}
