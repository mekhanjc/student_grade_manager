#include "studentManager.h"

#include "./ui_manager.h"
#include "printManager.h"
#include "studentArt.h"
#include "studentSci.h"

#include <QPushButton>
#include <QTextEdit>


StudentManager::StudentManager(QWidget *parent)
    : QManager(parent)
    , ui(new Ui::StudentManager)
{
    ui->setupUi(this);
    QString filePathStudent = "C:/Users/change05/Desktop/student.csv";
    QString filePathGrade = "C:/Users/change05/Desktop/grade.csv";
    readStudentFile(filePathStudent);
    readGradeFile(filePathGrade);

    PrintStudentManager *p = new PrintStudentManager;
    connect(ui->printButton, &QPushButton::clicked, [=](){
        p->printTable(ui->tableWidgetGrade);
    });

}

StudentManager::~StudentManager()
{
    delete ui;
}

void StudentManager::readStudentFile(const QString &filePath) {
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


void StudentManager::readGradeFile(const QString &filePath) {
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
