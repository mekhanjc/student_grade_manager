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
    void readGradeFile(const QString &filePath);
    void HeaderClicked(int column);

};
#endif // MAINWINDOW_H
