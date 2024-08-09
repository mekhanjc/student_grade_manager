#include "studentArt.h"

StudentArt::StudentArt() {
    this->economics = -1;
    this->arts = -1;
}
StudentArt::StudentArt(string name, string subject, int id) {
    setName(name);
    setSubject(subject);
    setId(id);
    this->economics = -1;
    this->arts = -1;
}
void StudentArt::setScore(int economics, int arts) {
    this->economics = economics;
    this->arts = arts;
    setavgScore((double)(economics + arts) / 2);
}
int StudentArt::getEconomics() const {
    return economics;
}
int StudentArt::getArts() const {
    return arts;
}
