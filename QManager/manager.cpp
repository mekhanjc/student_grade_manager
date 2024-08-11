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
#include <QMessageBox>




Manager::Manager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Manager)
{
    ui->setupUi(this);
    QString filePathGrade = "C:/Users/change10/Desktop/grade.csv";

    ui->studentTableWidget->setColumnWidth(4, 150);
    ui->studentTableWidget->setColumnWidth(5, 150);
    ui->studentTableWidget->setColumnWidth(6, 150);
    ui->studentTableWidget->setColumnWidth(7, 30);  //4567 칼럼 폭 조정


    readGradeFile(filePathGrade);

    PrintManager *p = new PrintManager;
    connect(ui->printButton, &QPushButton::clicked, [=](){
            p->printTable(ui->tableWidgetGrade);
    });

    connect(ui->openStudentButton, SIGNAL(clicked()), SLOT(openStudentFile()));
    connect(ui->saveStudentButton, SIGNAL(clicked()), SLOT(saveStudentFile()));
    connect(ui->registStudentButton, SIGNAL(clicked()), SLOT(registStudent()));
    connect(ui->deleteStudentButton, SIGNAL(clicked()), SLOT(deleteStudent()));
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
    student.setId(ui->IdLineEdit->text());
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

    QList<QString> list = {student.getId(), student.getName(),student.getGender(),student.getSubject(),
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
    layout->setAlignment(Qt::AlignCenter); // 체크박스 중앙정렬
    layout->setContentsMargins(0, 0, 0, 0); // 마진제거
    widget->setLayout(layout);

    ui->studentTableWidget->setCellWidget(rowNum, lastColumn, widget);
}

void Manager::deleteStudent() {

    bool Checked = false;

    for (int row = 0; row < ui->studentTableWidget->rowCount(); ++row) {
        QWidget *widget = ui->studentTableWidget->cellWidget(row, ui->studentTableWidget->columnCount() - 1);
        if (widget) {
            QCheckBox *checkbox = widget->findChild<QCheckBox *>(); //체크박스 위젯들을 하나씩 검사
            if (checkbox && checkbox->isChecked()) {
                Checked = true;
                break;
            }
        }
    }

    // 만약 체크된 체크박스가 있다면 삭제 처리 수행
    if (Checked) {
        for (int row = ui->studentTableWidget->rowCount() - 1; row >= 0; --row) {
            QWidget *widget = ui->studentTableWidget->cellWidget(row, ui->studentTableWidget->columnCount() - 1);
            if (widget) {
                QCheckBox *checkbox = widget->findChild<QCheckBox *>();
                if (checkbox && checkbox->isChecked()) {
                    ui->studentTableWidget->removeRow(row);
                }
            }
        }
    } else {

        QMessageBox::warning(this, "Warning", "삭제하려는 학생을 먼저 체크해주세요"); //체크된 체크박스가 없다면 경고창을 띄운다
    }

    // ui->studentTableWidget->removeRow(ui->studentTableWidget->currentRow());
    // ui->studentTableWidget->setCurrentCell(-1, -1);
}

void Manager::HeaderClicked(int column) {
    // 체크박스가 있는 칼럼의 인덱스를 확인합니다.
    int checkboxColumn = ui->studentTableWidget->columnCount() - 1;

    // 체크박스가 있는 칼럼이 클릭된 경우
    if (column == checkboxColumn) {
        bool allChecked = true;

        // 현재 모든 체크박스의 상태를 확인합니다.
        for (int row = 0; row < ui->studentTableWidget->rowCount(); ++row) {
            QWidget *widget = ui->studentTableWidget->cellWidget(row, checkboxColumn);
            if (widget) {
                QCheckBox *checkbox = widget->findChild<QCheckBox *>();
                if (checkbox && !checkbox->isChecked()) {
                    allChecked = false;
                    break;
                }
            }
        }

        // 체크박스의 상태를 반전시킵니다. (모두 선택 or 모두 해제)
        for (int row = 0; row < ui->studentTableWidget->rowCount(); ++row) {
            QWidget *widget = ui->studentTableWidget->cellWidget(row, checkboxColumn);
            if (widget) {
                QCheckBox *checkbox = widget->findChild<QCheckBox *>();
                if (checkbox) {
                    checkbox->setChecked(!allChecked);
                }
            }
        }
    }
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
