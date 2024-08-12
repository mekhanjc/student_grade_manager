#include "manager.h"

#include "./ui_manager.h"
#include "printManager.h"
#include "studentArt.h"
#include "studentSci.h"

#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QCheckBox>

Manager::Manager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Manager)
{
    ui->setupUi(this);
    QString filePathGrade = "C:/Users/change10/Desktop/grade.csv";

    readGradeFile(filePathGrade);

    PrintManager *p = new PrintManager;
    connect(ui->printButton, &QPushButton::clicked, [=](){
        p->printTable(ui->gradeTableWidget);
    });

    ui->studentTableWidget->setColumnWidth(0, 10);

    connect(ui->openStudentButton, SIGNAL(clicked()), SLOT(openStudentFile()));
    connect(ui->saveStudentButton, SIGNAL(clicked()), SLOT(saveStudentFile()));
    connect(ui->registStudentButton, SIGNAL(clicked()), SLOT(registStudent()));
    connect(ui->deleteStudentButton, SIGNAL(clicked()), SLOT(deleteStudent()));

    connect(ui->addSubjectButton, SIGNAL(clicked()), SLOT(addSubject()));
    connect(ui->deleteSubjectButton, SIGNAL(clicked()), SLOT(deleteSubject()));
    connect(ui->searchStudentButton, SIGNAL(clicked()), SLOT(searchStudent()));

    connect(ui->openGradeButton, SIGNAL(clicked()), SLOT(openGradeFile()));
    connect(ui->recallGradeButton, SIGNAL(clicked()), SLOT(recallGradeFile()));
    connect(ui->saveGradeButton, SIGNAL(clicked()), SLOT(saveGradeFile()));
    
    connect(ui->studentTableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &Manager::HeaderClicked);
    //체크박스 헤더 칼럼 클릭시 전체 체크 or 해제

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
    student.setId(rowNum+1);
    student.setName(ui->nameLineEdit->text());

    QString selectedGender;
    if (ui->maleRadioButton->isChecked()) {
        selectedGender = "남성";
    } else if (ui->femaleRadioButton->isChecked()) {
        selectedGender = "여성";
    } else {
        selectedGender = "없음";
    }
    student.setGender(selectedGender);

    student.setSubject(ui->majorComboBox->currentText());
    student.setBirthday(ui->birthLineEdit->text());
    student.setPhoneNumber(ui->phoneLineEdit->text());
    student.setAddress(ui->addressLineEdit->text());

    QList<QString> list = {QString::number(student.getId()), student.getName(), student.getGender(),
        student.getSubject(), student.getBirthday(), student.getPhoneNumber(), student.getAddress()};

    ui->studentTableWidget->insertRow(rowNum);
    for (int i = 1; i <= list.size(); ++i) {
        ui->studentTableWidget->setItem(rowNum, i, new QTableWidgetItem(list[i-1]));
        ui->studentTableWidget->item(rowNum, i)->setTextAlignment(Qt::AlignCenter);
    }

    QTableWidgetItem *checkboxItem = new QTableWidgetItem();
    checkboxItem->setCheckState(Qt::Unchecked);
    ui->studentTableWidget->setItem(rowNum, 0, checkboxItem);

    ui->nameLineEdit->clear();
    ui->majorComboBox->clear();
    ui->birthLineEdit->clear();
    ui->phoneLineEdit->clear();
    ui->addressLineEdit->clear();
}

void Manager::deleteStudent() {
    for (int row = ui->studentTableWidget->rowCount() - 1; row >= 0; --row) {
        QTableWidgetItem *checkboxItem = ui->studentTableWidget->item(row, 0);
        if (checkboxItem && checkboxItem->checkState() == Qt::Checked) {
            ui->studentTableWidget->removeRow(row);
        }
    }
}


void Manager::addSubject() {

    bool ok;
    QString subjectName = QInputDialog::getText(this, tr("과목 추가"),
                                                tr("과목명 : "), QLineEdit::Normal,
                                                QString(), &ok);

    if (ok && !subjectName.isEmpty()) {
        int currentColumnCount = ui->gradeTableWidget->columnCount();
        int positionToAdd = currentColumnCount - 1;

        ui->gradeTableWidget->insertColumn(positionToAdd);
        ui->gradeTableWidget->setHorizontalHeaderItem(positionToAdd, new QTableWidgetItem(subjectName));

        int rowCount = ui->gradeTableWidget->rowCount();
        for (int row = 0; row < rowCount; ++row) {
            ui->gradeTableWidget->setItem(row, positionToAdd, new QTableWidgetItem());
        }
    }
}

void Manager::deleteSubject() {

    bool ok;
    QString subjectName = QInputDialog::getText(this, tr("과목 삭제"),
                                                tr("과목명 : "), QLineEdit::Normal,
                                                QString(), &ok);

    if (ok && !subjectName.isEmpty()) {
        int columnCount = ui->gradeTableWidget->columnCount();

        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem *headerItem = ui->gradeTableWidget->horizontalHeaderItem(col);
            if (headerItem && headerItem->text() == subjectName) {
                ui->gradeTableWidget->removeColumn(col);
                return;
            }
        }
        QMessageBox::warning(this, tr("Column Not Found"), tr("'%1' 과목을 찾을 수 없습니다.").arg(subjectName));
    }
}

void Manager::searchStudent() {
    bool ok;
    QString studentName = QInputDialog::getText(this, tr("학생 이름 검색"),
                                                tr("이름 : "), QLineEdit::Normal,
                                                QString(), &ok);

    if (ok && !studentName.isEmpty()) {
        int rowCount = ui->gradeTableWidget->rowCount();
        bool found = false;

        for (int row = 0; row < rowCount; ++row) {
            ui->gradeTableWidget->setRowHidden(row, true);
        }

        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem *nameItem = ui->gradeTableWidget->item(row, 0);
            if (nameItem && nameItem->text().contains(studentName, Qt::CaseInsensitive)) {
                ui->gradeTableWidget->setRowHidden(row, false);
                found = true;
            }
        }

        if (!found) {
            QMessageBox::information(this, tr("No Results"), tr("이름이 '%1'인 학생은 없습니다.").arg(studentName));
        }
    }
}


void Manager::openGradeFile() {
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
    ui->gradeTableWidget->setRowCount(rowCount);
    ui->gradeTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        ui->gradeTableWidget->insertRow(rowCount);
        for (int i = 0; i < fields.size(); ++i) {
            ui->gradeTableWidget->setItem(rowCount, i, new QTableWidgetItem(fields[i]));
        }
        ++rowCount;
    }

    ui->gradeTableWidget->setSortingEnabled(true);
}

void Manager::recallGradeFile() {

}

void Manager::saveGradeFile() {

}


//-------------------------아래는 수정 필요-----------------------------------



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
    ui->gradeTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (firstLine) {
            ui->gradeTableWidget->setColumnCount(fields.size());
            ui->gradeTableWidget->setHorizontalHeaderLabels(fields);

            firstLine = false;
        } else {
            ui->gradeTableWidget->insertRow(rowCount);
            // ui->listWidget->insertItem(1, fields.at(1));
            for (int i = 0; i < fields.size(); ++i) {
                ui->gradeTableWidget->setItem(rowCount, i, new QTableWidgetItem(fields[i]));
            }
            ++rowCount;
        }
    }

    ui->gradeTableWidget->setSortingEnabled(true);
    file.close();
}
