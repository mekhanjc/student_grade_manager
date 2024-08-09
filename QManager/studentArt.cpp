#include "studentArt.h"

StudentArt::StudentArt() {

}
StudentArt::StudentArt(QString name, QString subject, int id) {
    setName(name);
    setSubject(subject);
    setId(id);
    this->economics = -1;
    this->arts = -1;
}
void StudentArt::setScore(QString subject, int score) {
    this-> ArtSubjectList[subject] = score;
}
int StudentArt::getEconomics() const {
    return economics;
}
int StudentArt::getArts() const {
    return arts;
}
