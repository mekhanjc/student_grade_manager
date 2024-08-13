#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "studentArt.h"
#include "studentSci.h"

#include <QMainWindow>
#include <QFile>
#include <QTableWidget>
#include <QList>

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

private:
    Ui::Manager *ui;
    QList<StudentArt> studentArtList;
    QList<StudentSci> studentSciList;

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
};
#endif // MAINWINDOW_H
