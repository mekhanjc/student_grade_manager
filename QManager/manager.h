#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "studentArt.h"
#include "studentSci.h"

#include <QMainWindow>
#include <QFile>
#include <QTableWidget>
#include <QList>
#include <QVector>

class QMdiArea;

QT_BEGIN_NAMESPACE
namespace Ui {
class Manager;
}
QT_END_NAMESPACE

class Manager : public QMainWindow
{
    Q_OBJECT
    QMdiArea *mdiArea;

public:
    Manager(QWidget *parent = nullptr);
    ~Manager();
    void createMenubar();

private:
    Ui::Manager *ui;
    QVector<Student*> studentList; // 등록된 학생 객체를 저장하는 멤버 변수

    QVector<QString> artSubjectList; // 문과 과목 저장
    QVector<QString> sciSubjectList; // 이과 과목 저장

public slots:
    void openStudentFile();
    void saveStudentFile();
    void registStudent();
    void deleteStudent();

    void addSubject();
    void deleteSubject();

    void searchStudent();
    void deleteGrade();

    void recallGradeFile();

    void updateRowAverages(int row, int column);
    void studentHeaderClicked(int column);
    void gradeHeaderClicked(int column);

    void showHelp();
    void classifySubject();
};
#endif // MAINWINDOW_H
