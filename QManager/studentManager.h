#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <QMainWindow>
#include <QFile>

class StudentManager : public QObject {
    Q_OBJECT

public:
    explicit StudentManager(QObject *parent = nullptr);

public slots:
    void readStudentFile(const QString &filePath);
};

#endif // STUDENTMANAGER_H
