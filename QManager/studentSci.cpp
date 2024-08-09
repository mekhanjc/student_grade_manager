#include "studentSci.h"

StudentSci::StudentSci() {
    this->science = -1;
    this->math = -1;
}

StudentSci::StudentSci(string name, string subject, int id) {
    setName(name);
    setSubject(subject);
    setId(id);
    this->science = -1;
    this->math = -1;
}

void StudentSci::setScore(int science, int math) {
    this->science = science;
    this->math = math;
    setavgScore((double)(science + math) / 2);
}

int StudentSci::getScience() const {
    return science;
}

int StudentSci::getMath() const  {
    return math;
}
