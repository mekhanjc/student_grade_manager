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
    connect(ui->gradeTableWidget, &QTableWidget::cellChanged, this, &Manager::updateRowAverages);
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

    int rowCount = 0;
    ui->studentTableWidget->setRowCount(rowCount);
    ui->studentTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        ui->studentTableWidget->insertRow(rowCount);

        for (int i = 1; i < fields.size(); ++i) {
            ui->studentTableWidget->setItem(rowCount, i, new QTableWidgetItem(fields[i]));
        }
        int firstColumn = 0;
        QCheckBox *checkbox = new QCheckBox();
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);

        layout->addWidget(checkbox);
        layout->setAlignment(Qt::AlignCenter); // 체크박스 중앙정렬
        layout->setContentsMargins(0, 0, 0, 0); // 마진제거
        widget->setLayout(layout);

        ui->studentTableWidget->setCellWidget(rowCount, firstColumn, widget);
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

    ui->studentTableWidget->setSortingEnabled(false);

    Student student;
    int rowNum = ui->studentTableWidget->rowCount();

    QString id = ui->idLineEdit->text();
    student.setId(id.toInt());
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


    int firstColumn = 0;
    QCheckBox *checkbox = new QCheckBox();
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);

    layout->addWidget(checkbox);
    layout->setAlignment(Qt::AlignCenter); // 체크박스 중앙정렬
    layout->setContentsMargins(0, 0, 0, 0); // 마진제거
    widget->setLayout(layout);

    ui->studentTableWidget->setCellWidget(rowNum, firstColumn, widget);

    for (int i = 1; i <= list.size(); ++i) {
        if (i == 1) {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setData(Qt::EditRole, list[i-1].toInt());
            ui->studentTableWidget->setItem(rowNum, i, item);
        }
        else
            ui->studentTableWidget->setItem(rowNum, i, new QTableWidgetItem(list[i-1]));

        ui->studentTableWidget->item(rowNum, i)->setTextAlignment(Qt::AlignCenter);
    }

    ui->studentTableWidget->setSortingEnabled(true);

    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->birthLineEdit->clear();
    ui->phoneLineEdit->clear();
    ui->addressLineEdit->clear();
}

void Manager::deleteStudent() {
    ui->studentTableWidget->removeRow(ui->studentTableWidget->currentRow());
    ui->studentTableWidget->setCurrentCell(-1, -1);

    bool Checked = false;

    for (int row = 0; row < ui->studentTableWidget->rowCount(); ++row) {
        QWidget *widget = ui->studentTableWidget->cellWidget(row, 0);
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
            QWidget *widget = ui->studentTableWidget->cellWidget(row, 0);
            if (widget) {
                QCheckBox *checkbox = widget->findChild<QCheckBox *>();
                if (checkbox && checkbox->isChecked()) {
                    ui->studentTableWidget->removeRow(row);
                }
            }
        }
    } else {

        QMessageBox::warning(this, "경고", "삭제하려는 학생을 먼저 체크해주세요"); //체크된 체크박스가 없다면 경고창을 띄운다
    }

    // ui->studentTableWidget->removeRow(ui->studentTableWidget->currentRow());
    // ui->studentTableWidget->setCurrentCell(-1, -1);
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
        if (subjectName == "학번" || subjectName == "이름" || subjectName == "평균") {
            QString message = subjectName + "은 삭제할 수 없습니다";
            QMessageBox::warning(this, "삭제 불가", message, QMessageBox::Ok);
            return;
        }

        int columnCount = ui->gradeTableWidget->columnCount();

        for (int col = 0; col < columnCount; ++col) {
            QTableWidgetItem *headerItem = ui->gradeTableWidget->horizontalHeaderItem(col);
            if (headerItem && headerItem->text() == subjectName) {
                ui->gradeTableWidget->removeColumn(col);
                return;
            }
        }
        QMessageBox::warning(this, tr("검색 실패"), tr("'%1' 과목을 찾을 수 없습니다.").arg(subjectName));
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
            QMessageBox::information(this, tr("결과 없음"), tr("이름이 '%1'인 학생은 없습니다.").arg(studentName));
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

        if (firstLine) {
            ui->gradeTableWidget->insertColumn(0);
            fields.prepend("선택");
            ui->gradeTableWidget->setColumnCount(fields.size());
            ui->gradeTableWidget->setHorizontalHeaderLabels(fields);
            firstLine = false;
        } else {
            ui->gradeTableWidget->insertRow(rowCount);
            for (int i = 1; i <= fields.size(); ++i) {
                ui->gradeTableWidget->setItem(rowCount, i, new QTableWidgetItem(fields[i-1]));
            }
            QCheckBox *checkbox = new QCheckBox();
            QWidget *widget = new QWidget();
            QHBoxLayout *layout = new QHBoxLayout(widget);

            layout->addWidget(checkbox);
            layout->setAlignment(Qt::AlignCenter); // 체크박스 중앙정렬
            layout->setContentsMargins(0, 0, 0, 0); // 마진제거
            widget->setLayout(layout);

            ui->studentTableWidget->setCellWidget(rowCount, 0, widget);
            ++rowCount;
        }
    }




    ui->gradeTableWidget->setSortingEnabled(true);
}

void Manager::recallGradeFile() {

}

void Manager::saveGradeFile() {

}


void Manager::HeaderClicked(int column) {
    // 체크박스가 있는 칼럼의 인덱스를 확인합니다.
    int checkboxColumn = 0;

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


void Manager::updateRowAverages(int row, int column) {
    QTableWidgetItem *item = ui->gradeTableWidget->item(row, column);
    if (!item || item->text().isEmpty()) {
        return;
    }

    double sum = 0.0;
    int count = 0;
    int colCount = ui->gradeTableWidget->columnCount();

    for (int i = 0; i < colCount - 1; ++i) { // 마지막 열 제외
        QTableWidgetItem *cellItem = ui->gradeTableWidget->item(row, i);
        if (cellItem && !cellItem->text().isEmpty()) {
            bool ok;
            double value = cellItem->text().toDouble(&ok);
            if (ok) {
                sum += value;
                ++count;
            }
        }
    }

    double average = (count > 0) ? (sum / count) : 0.0;

    QTableWidgetItem *averageItem = ui->gradeTableWidget->item(row, colCount - 1);
    if (!averageItem) {
        averageItem = new QTableWidgetItem();
        ui->gradeTableWidget->setItem(row, colCount - 1, averageItem);
    }
    averageItem->setText(QString::number(average, 'f', 2));
    averageItem->setTextAlignment(Qt::AlignCenter);
}
