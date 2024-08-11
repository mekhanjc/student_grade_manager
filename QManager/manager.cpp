#include "manager.h"

#include "./ui_manager.h"
#include "printManager.h"
#include "studentArt.h"
#include "studentSci.h"

#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QCheckBox>
#include <QTableWidget>




Manager::Manager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Manager)
{
    ui->setupUi(this);
    QString filePathGrade = "C:/Users/change10/Desktop/grade.csv";

    readGradeFile(filePathGrade);

    PrintManager *p = new PrintManager;
    connect(ui->printButton, &QPushButton::clicked, [=](){
            p->printTable(ui->tableWidgetGrade);
    });

    connect(ui->openStudentButton, SIGNAL(clicked()), SLOT(openStudentFile()));
    connect(ui->saveStudentButton, SIGNAL(clicked()), SLOT(saveStudentFile()));
    connect(ui->registStudentButton, SIGNAL(clicked()), SLOT(registStudent()));
    connect(ui->deleteStudentButton, SIGNAL(clicked()), SLOT(deleteStudent()));

}

Manager::~Manager()
{
    delete ui;
}


void Manager::openStudentFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "CSV Files (*.csv);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::LastEncoding);

    bool firstLine = true;
    int rowCount = 0;
    ui->studentTableWidget->setRowCount(rowCount);
    ui->studentTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        ui->studentTableWidget->insertRow(rowCount);
        for (int i = 0; i < fields.size(); ++i) {
            ui->studentTableWidget->setItem(rowCount, i, new QTableWidgetItem(fields[i]));
        }
        ++rowCount;
    }

    ui->studentTableWidget->setSortingEnabled(true);
}

void Manager::saveStudentFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "CSV Files (*.csv);;All Files (*)");
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::LastEncoding);

    // Write table data
    for (int row = 0; row < ui->studentTableWidget->rowCount(); ++row) {
        QStringList rowItems;
        for (int col = 0; col < ui->studentTableWidget->columnCount(); ++col) {
            QTableWidgetItem* item = ui->studentTableWidget->item(row, col);
            if (item) {
                rowItems << item->text();
            } else {
                rowItems << "";
            }
        }
        out << rowItems.join(',') << '\n';
    }

    file.close();
}

void Manager::registStudent() {

    Student student;
    int rowNum = ui->studentTableWidget->rowCount();
    student.setId(rowNum);
    student.setName(ui->nameLineEdit->text());
    student.setBirthday(ui->birthLineEdit->text());
    student.setPhone(ui->phoneLineEdit->text());
    student.setAddress(ui->addressLineEdit->text());

    if (ui->majorComboBox->currentIndex()){
        student.setSubject("이과");
    } else {
        student.setSubject("문과");
    }

    if (ui->maleRadioButton->isChecked()) {
        student.setGender("남성");
    } else if(ui->femaleRadioButton->isChecked()) {
        student.setGender("여성");
    }

    QList<QString> list = {QString::number(student.getId()), student.getName(),student.getGender(),student.getSubject(),
                           student.getBirthday(), student.getPhone(), student.getAddress()};

    ui->studentTableWidget->insertRow(rowNum);
    for (int i = 0; i < list.size(); ++i) {
        ui->studentTableWidget->setItem(rowNum, i, new QTableWidgetItem(list[i]));
        ui->studentTableWidget->item(rowNum, i)->setTextAlignment(Qt::AlignCenter); // 학생관리 테이블위젯 텍스트들 중앙정렬
        qDebug() << ui->studentTableWidget;
    }
    int lastColumn = ui->studentTableWidget->columnCount() - 1;
    QCheckBox *checkbox = new QCheckBox();
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);

    layout->addWidget(checkbox);
    layout->setAlignment(Qt::AlignCenter); // Center the checkbox in the layout
    layout->setContentsMargins(0, 0, 0, 0); // Remove margins to fully center the checkbox
    widget->setLayout(layout);

    ui->studentTableWidget->setCellWidget(rowNum, lastColumn, widget);
}

void Manager::deleteStudent() {
    ui->studentTableWidget->removeRow(ui->studentTableWidget->currentRow());
    ui->studentTableWidget->setCurrentCell(-1, -1);
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
