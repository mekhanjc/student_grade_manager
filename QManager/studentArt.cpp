#include "studentArt.h"

StudentArt::StudentArt() {

}
StudentArt::StudentArt(QString name, QString subject, QString id, QString gender,
                       QString birthday, QString phonenumber, QString address) {
    setName(name);
    setSubject(subject);
    setId(id);
}
void StudentArt::setScore(QString subject, int score) {
    this-> ArtSubjectList[subject] = score;
}
