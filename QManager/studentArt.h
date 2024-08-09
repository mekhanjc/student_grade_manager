#ifndef STUDENTART_H
#define STUDENTART_H

#include "student.h"

class StudentArt : public Student {
    int economics;
    int arts;
public:
    StudentArt();
    StudentArt(string name, string subject, int id);
    void setScore(int economics, int arts);
    int getEconomics() const;
    int getArts() const;

};

#endif // STUDENTART_H
