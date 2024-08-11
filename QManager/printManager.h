#ifndef PRINTMANAGER_H
#define PRINTMANAGER_H

#include <QTableWidget>
#include <QtPrintSupport/QPrinter>

class PrintManager : public QObject {
    Q_OBJECT

public:
    explicit PrintManager(QObject *parent = nullptr);

    void printTable(QTableWidget *tableWidget);

private:
    void print(QPrinter &printer, QTableWidget *tableWidget);
};

#endif // PRINTMANAGER_H
