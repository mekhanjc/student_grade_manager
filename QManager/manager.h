#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>


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

public slots:
    void openStudentFile();
    void saveStudentFile();
    void registStudent();
    void deleteStudent();

    void addSubject();
    void deleteSubject();
    void searchStudent();
    void openGradeFile();
    void recallGradeFile();
    void saveGradeFile();

    void HeaderClicked(int column);
    void readGradeFile(const QString &filePath);
};
#endif // MAINWINDOW_H
