#include "manager.h"

#include "./ui_manager.h"
#include "printManager.h"
#include "studentArt.h"
#include "studentSci.h"

#include <QPushButton>
#include <QTextEdit>




Manager::Manager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Manager)
{
    ui->setupUi(this);
    QString filePathStudent = "C:/Users/change10/Desktop/student.csv";
    QString filePathGrade = "C:/Users/change10/Desktop/grade.csv";
    readStudentFile(filePathStudent);
    readGradeFile(filePathGrade);

    PrintManager *p = new PrintManager;
    connect(ui->printButton, &QPushButton::clicked, [=](){
            p->printTable(ui->tableWidgetGrade);
    });




}

Manager::~Manager()
{
    delete ui;
}

void Manager::readStudentFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }

    QTextStream in(&file);

    bool firstLine = true;
    int rowCount = 0;
    in.setEncoding(QStringConverter::LastEncoding);
    ui->tableWidgetStudent->setEditTriggers(QTableWidget::NoEditTriggers);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        ui->tableWidgetStudent->insertRow(rowCount);
        for (int i = 0; i < fields.size(); ++i) {
            ui->tableWidgetStudent->setItem(rowCount, i, new QTableWidgetItem(fields[i]));
        }
        ++rowCount;
    }

    ui->tableWidgetStudent->setSortingEnabled(true);
}


void Manager::readGradeFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    QStringList headers;

    bool firstLine = true;
    int rowCount = 0;
    in.setEncoding(QStringConverter::LastEncoding);
    ui->tableWidgetGrade->setEditTriggers(QTableWidget::NoEditTriggers);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (firstLine) {
            ui->tableWidgetGrade->setColumnCount(fields.size());
            ui->tableWidgetGrade->setHorizontalHeaderLabels(fields);

            firstLine = false;
        } else {
            ui->tableWidgetGrade->insertRow(rowCount);
            // ui->listWidget->insertItem(1, fields.at(1));
            for (int i = 0; i < fields.size(); ++i) {
                ui->tableWidgetGrade->setItem(rowCount, i, new QTableWidgetItem(fields[i]));
            }
            ++rowCount;
        }
    }

    ui->tableWidgetGrade->setSortingEnabled(true);
    file.close();
}
