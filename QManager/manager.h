#ifndef MANAGER_H
#define MANAGER_H

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
    void readStudentFile(const QString &filePath);
    void readGradeFile(const QString &filePath);
    void print(const QString &filePath);
};
#endif // MANAGER_H
