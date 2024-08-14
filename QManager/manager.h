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
    void createMenubar();

    QAction *makeAction(QString icon, QString name, QString toolTip, QObject* recv, const char* slot);

private:
    Ui::Manager *ui;
    QList<StudentArt*> studentArtList; // 문과 학생 객체를 저장
    QList<StudentSci*> studentSciList; // 이과 학생 객체를 저장


public slots:
    void openStudentFile();
    void saveStudentFile();
    void registStudent();
    void deleteStudent();

    void addSubject();
    void deleteSubject();

    void searchStudent();
    void deleteGrade();

    void updateRowAverages(int row, int column);
    void studentHeaderClicked(int column);
    void gradeHeaderClicked(int column);

    void showHelp();
    void classifySubject();

    void enableTableWidgetEditing();
    void disableTableWidgetEditing();


};
#endif // MAINWINDOW_H
