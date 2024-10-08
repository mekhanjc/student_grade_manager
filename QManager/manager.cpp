#include "manager.h"

#include "./ui_manager.h"
#include "printManager.h"
#include "studentArt.h"
#include "studentSci.h"
#include "subjectDialog.h"

#include <QPushButton>
#include <QTextEdit>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QCheckBox>
#include <QAction>


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
    ui->gradeTableWidget->setColumnWidth(0, 10);

    ui->studentTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->gradeTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);



    createMenubar();

    connect(ui->openStudentButton, SIGNAL(clicked()), SLOT(openStudentFile()));
    connect(ui->saveStudentButton, SIGNAL(clicked()), SLOT(saveStudentFile()));
    connect(ui->registStudentButton, SIGNAL(clicked()), SLOT(registStudent()));
    connect(ui->deleteStudentButton, SIGNAL(clicked()), SLOT(deleteStudent()));

    connect(ui->addSubjectButton, SIGNAL(clicked()), SLOT(addSubject()));
    connect(ui->deleteSubjectButton, SIGNAL(clicked()), SLOT(deleteSubject()));

    connect(ui->searchStudentButton, SIGNAL(clicked()), SLOT(searchStudent()));
    connect(ui->deleteGradeButton, SIGNAL(clicked()), SLOT(deleteGrade()));

    connect(ui->openGradeButton, SIGNAL(clicked()), SLOT(openStudentFile()));
    connect(ui->saveGradeButton, SIGNAL(clicked()), SLOT(saveStudentFile()));

    connect(ui->studentTableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &Manager::studentHeaderClicked);
    connect(ui->gradeTableWidget->horizontalHeader(), &QHeaderView::sectionClicked, this, &Manager::gradeHeaderClicked);
    connect(ui->gradeTableWidget, &QTableWidget::cellChanged, this, &Manager::updateRowAverages);

    //도움말 푸쉬버튼 connect
    connect(ui->helppushButton_1, SIGNAL(clicked()), SLOT(showHelp()));
    connect(ui->helppushButton_2, SIGNAL(clicked()), SLOT(showHelp()));
    connect(ui->helppushButton_3, SIGNAL(clicked()), SLOT(showHelp()));

    //성적관리탭 문과 이과 분류
    connect(ui->gradecomboBox, SIGNAL(currentIndexChanged(int)), SLOT(classifySubject()));
    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, [&](int index){
        if(index == 2)
        p->printPreviewTable(ui->gradeTableWidget, ui->frame);
    });


    connect(ui->enableInputButton, SIGNAL(clicked()), this, SLOT(enableTableWidgetEditing()));
    connect(ui->disableInputButton, SIGNAL(clicked()), this, SLOT(disableTableWidgetEditing()));


    ui->helppushButton_1->setIcon(QIcon(":/icons/help.png"));
    ui->helppushButton_2->setIcon(QIcon(":/icons/help.png"));
    ui->helppushButton_3->setIcon(QIcon(":/icons/help.png"));
}

Manager::~Manager()
{
    delete ui;
}


void Manager::openStudentFile() {
    // 초기화
    studentArtList.clear();
    studentSciList.clear();
    subjectArtList.clear();
    subjectSciList.clear();

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
    ui->gradeTableWidget->setRowCount(rowCount);
    ui->studentTableWidget->setEditTriggers(QTableWidget::NoEditTriggers);


    int studentHeaderSize = 8;

    // Read the first line to check the header
    QString firstLine = in.readLine();
    QString expectedHeader = "선택,학번,이름,성별,학과,생년월일,전화번호,주소";

    if (!firstLine.startsWith(expectedHeader)) {
        QMessageBox::warning(nullptr, "Invalid File", "유효한 형식의 파일을 선택해주세요.");
        file.close();
        return;
    }

    QStringList headers = firstLine.split(",");

    // Set headers
    ui->studentTableWidget->setHorizontalHeaderLabels(headers);

    QStringList sartList = in.readLine().split(",");
    QStringList ssciList = in.readLine().split(",");
    subjectArtList.append(sartList.toList());
    subjectSciList.append(ssciList.toList());
    QStringList gradeHeaders = {"선택", "학번", "이름"};
    QStringList uniqueList;
    uniqueList << sartList;
    uniqueList << ssciList;
    uniqueList.removeDuplicates();
    gradeHeaders.append(uniqueList);
    gradeHeaders.append("평균");
    ui->gradeTableWidget->setColumnCount(uniqueList.size() + 4);
    ui->gradeTableWidget->setHorizontalHeaderLabels(gradeHeaders);



    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        ui->studentTableWidget->insertRow(rowCount);
        ui->gradeTableWidget->insertRow(rowCount);

        Student* student = new Student();

        for (int i = 1; i < studentHeaderSize; ++i) {
            QTableWidgetItem* item = new QTableWidgetItem(fields[i]);
            item->setTextAlignment(Qt::AlignCenter);
            ui->studentTableWidget->setItem(rowCount, i, item);
            switch (i) {
            case 1: student->setId(fields[i].toInt());break;
            case 2: student->setName(fields[i]);break;
            case 3: student->setGender(fields[i]); break;
            case 4: student->setSubject(fields[i]); break;
            case 5: student->setBirthday(fields[i]); break;
            case 6: student->setPhoneNumber(fields[i]); break;
            case 7: student->setAddress(fields[i]); break;
            }
        }

        if (student->getSubject() == "문과") {
            StudentArt *studentArt = static_cast<StudentArt*>(student);
            if (studentArt) {
                studentArtList.append(studentArt);
            }
        } else if (student->getSubject() == "이과") {
            StudentSci *studentSci = static_cast<StudentSci*>(student);
            if (studentSci) {
                studentSciList.append(studentSci);
            }
        }

        for (int i = studentHeaderSize + 1; i < fields.size(); ++i) {
            QTableWidgetItem* item = new QTableWidgetItem(fields[i]);
            item->setTextAlignment(Qt::AlignCenter);
            ui->gradeTableWidget->setItem(rowCount, i - studentHeaderSize, item);
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

        checkbox = new QCheckBox();
        widget = new QWidget();
        layout = new QHBoxLayout(widget);

        layout->addWidget(checkbox);
        layout->setAlignment(Qt::AlignCenter); // 체크박스 중앙정렬
        layout->setContentsMargins(0, 0, 0, 0); // 마진제거
        widget->setLayout(layout);

        ui->gradeTableWidget->setCellWidget(rowCount, firstColumn, widget);
        ++rowCount;
    }

    ui->studentTableWidget->setSortingEnabled(true);
    ui->gradeTableWidget->setSortingEnabled(true);
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

    // Write headers
    QStringList headers, artHeaders, sciHeaders;
    for (int col = 0; col < ui->studentTableWidget->columnCount(); ++col) {
        headers << ui->studentTableWidget->horizontalHeaderItem(col)->text();
    }

    out << headers.join(',') << '\n';

    // 문과 헤더 추가
    for (int i = 0; i < subjectArtList.size(); ++i) {
        artHeaders << subjectArtList[i];
    }
    out << artHeaders.join(',') << '\n';

    // 이과 헤더 추가
    for (int i = 0; i < subjectSciList.size(); ++i) {
        sciHeaders << subjectSciList[i];
    }
    out << sciHeaders.join(',') << '\n';

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

        QString id = ui->studentTableWidget->item(row, 1)->text();
        for (int rowNum = ui->gradeTableWidget->rowCount() - 1; rowNum >= 0; --rowNum) {
            if (ui->gradeTableWidget->item(rowNum, 1)->text() == id) {
                for (int col = 0; col < ui->gradeTableWidget->columnCount(); ++col) {
                    QTableWidgetItem* item = ui->gradeTableWidget->item(rowNum, col);
                    if (item) {
                        rowItems << item->text();
                    } else {
                        rowItems << "";
                    }
                }
                break;
            }
        }

        out << rowItems.join(',') << '\n';
    }

    file.close();
}

void Manager::registStudent() {

    ui->studentTableWidget->setSortingEnabled(false);

    Student* student = new Student();
    int rowNum = ui->studentTableWidget->rowCount();

    QString id = ui->idLineEdit->text();
    student->setId(id.toInt());
    student->setName(ui->nameLineEdit->text());

    QString selectedGender;
    if (ui->maleRadioButton->isChecked()) {
        selectedGender = "남성";
    } else if (ui->femaleRadioButton->isChecked()) {
        selectedGender = "여성";
    } else {
        selectedGender = "없음";
    }
    student->setGender(selectedGender);

    student->setSubject(ui->majorComboBox->currentText());
    student->setBirthday(ui->birthLineEdit->text());
    student->setPhoneNumber(ui->phoneLineEdit->text());
    student->setAddress(ui->addressLineEdit->text());

    if (student->getSubject() == "문과") {
        StudentArt *studentArt = static_cast<StudentArt*>(student);
        if (studentArt) {
            studentArtList.append(studentArt);
        }
    } else if (student->getSubject() == "이과") {
        StudentSci *studentSci = static_cast<StudentSci*>(student);
        if (studentSci) {
            studentSciList.append(studentSci);
        }
    }

    QList<QString> list = {QString::number(student->getId()), student->getName(), student->getGender(),
                           student->getSubject(), student->getBirthday(), student->getPhoneNumber(), student->getAddress()};

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

    ui->gradeTableWidget->setSortingEnabled(false);
    ui->gradeTableWidget->insertRow(rowNum);
    QTableWidgetItem *item = new QTableWidgetItem;
    item->setData(Qt::EditRole, list[0].toInt());
    item->setTextAlignment(Qt::AlignCenter);
    ui->gradeTableWidget->setItem(rowNum, 1, item);
    item = new QTableWidgetItem(list[1]);
    item->setTextAlignment(Qt::AlignCenter);
    ui->gradeTableWidget->setItem(rowNum, 2, item);
    for (int column = 3; column < ui->gradeTableWidget->columnCount()-1; ++column) {
        item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        ui->gradeTableWidget->setItem(rowNum, column, item);
    }

    checkbox = new QCheckBox();
    widget = new QWidget();
    layout = new QHBoxLayout(widget);
    layout->addWidget(checkbox);
    layout->setAlignment(Qt::AlignCenter); // 체크박스 중앙정렬
    layout->setContentsMargins(0, 0, 0, 0); // 마진제거
    widget->setLayout(layout);
    ui->gradeTableWidget->setCellWidget(rowNum, 0, widget);

    ui->gradeTableWidget->setSortingEnabled(true);


    ui->studentTableWidget->setSortingEnabled(true);

    ui->idLineEdit->clear();
    ui->nameLineEdit->clear();
    ui->birthLineEdit->clear();
    ui->phoneLineEdit->clear();
    ui->addressLineEdit->clear();

}

void Manager::deleteStudent() {

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
                    QString id = ui->studentTableWidget->item(row, 1)->text();
                    QString subject = ui->studentTableWidget->item(row, 4)->text();

                    ui->studentTableWidget->removeRow(row);

                    // 성적 테이블에서 삭제
                    for (int rowNum = ui->gradeTableWidget->rowCount() - 1; rowNum >= 0; --rowNum) {
                        if (ui->gradeTableWidget->item(rowNum, 1)->text() == id) {
                            ui->gradeTableWidget->removeRow(rowNum);
                            break;
                        }
                    }
                    // 학생 리스트에서 삭제
                    if (subject == "문과") {
                        for (int rowNum = studentArtList.size() - 1; rowNum >= 0; --rowNum) {
                            if (studentArtList[rowNum]->getId() == id.toInt()) {
                                studentArtList.removeAt(rowNum);
                                break;
                            }
                        }
                    }
                    else if (subject == "이과") {
                        for (int rowNum = studentSciList.size() - 1; rowNum >= 0; --rowNum) {
                            if (studentSciList[rowNum]->getId() == id.toInt()) {
                                studentSciList.removeAt(rowNum);
                                break;
                            }
                        }
                    }
                }
            }
        }
    } else {
        QMessageBox::warning(this, "경고", "삭제하려는 학생을 먼저 체크해주세요"); //체크된 체크박스가 없다면 경고창을 띄운다
    }
}



void Manager::addSubject() {

    SubjectDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString subjectName = dialog.getSubjectName();
        QString selectedOption = dialog.getSelectedOption();

        int currentColumnCount = ui->gradeTableWidget->columnCount();
        int positionToAdd = currentColumnCount - 1;

        if (!subjectName.isEmpty()) {
            ui->gradeTableWidget->insertColumn(positionToAdd);
            ui->gradeTableWidget->setHorizontalHeaderItem(positionToAdd, new QTableWidgetItem(subjectName));

            int rowCount = ui->gradeTableWidget->rowCount();
            for (int row = 0; row < rowCount; ++row) {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setTextAlignment(Qt::AlignCenter);
                ui->gradeTableWidget->setItem(row, positionToAdd, item);
            }
        }

        if (selectedOption == "문과") {
            subjectArtList.append(subjectName);
            if (ui->gradecomboBox->currentText() == "이과")
                ui->gradeTableWidget->setColumnHidden(positionToAdd, true);

        } else if (selectedOption == "이과") {
            subjectSciList.append(subjectName);
            if (ui->gradecomboBox->currentText() == "문과")
                ui->gradeTableWidget->setColumnHidden(positionToAdd, true);
        } else {
            subjectSciList.append(subjectName);
            subjectArtList.append(subjectName);
        }

    }
}

void Manager::deleteSubject() {

    bool ok;
    QString subjectName = QInputDialog::getText(this, tr("과목 삭제"),
                                                tr("과목명 : "), QLineEdit::Normal,
                                                QString(), &ok);

    if (ok && !subjectName.isEmpty()) {
        if (subjectName == "선택" || subjectName == "학번" || subjectName == "이름" || subjectName == "평균") {
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
    ui->gradecomboBox->setCurrentIndex(0);

    int rowCount = ui->gradeTableWidget->rowCount();
    if (ok && !studentName.isEmpty()) {
        bool found = false;

        for (int row = 0; row < rowCount; ++row) {
            ui->gradeTableWidget->setRowHidden(row, true);
        }

        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem *nameItem = ui->gradeTableWidget->item(row, 2);
            if (nameItem && nameItem->text().contains(studentName, Qt::CaseInsensitive)) {
                ui->gradeTableWidget->setRowHidden(row, false);
                found = true;
            }
        }

        if (!found) {
            QMessageBox::information(this, tr("결과 없음"), tr("이름이 '%1'인 학생은 없습니다.").arg(studentName));
        }
    } else if (studentName.isEmpty()) {
        for (int row = 0; row < rowCount; ++row) {
            ui->gradeTableWidget->setRowHidden(row, false);
        }
    }
}

void Manager::deleteGrade() {
    bool Checked = false;

    for (int row = 0; row < ui->gradeTableWidget->rowCount(); ++row) {
        QWidget *widget = ui->gradeTableWidget->cellWidget(row, 0);
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
        for (int row = ui->gradeTableWidget->rowCount() - 1; row >= 0; --row) {
            QWidget *widget = ui->gradeTableWidget->cellWidget(row, 0);
            if (widget) {
                QCheckBox *checkbox = widget->findChild<QCheckBox *>();
                if (checkbox && checkbox->isChecked()) {
                    for (int column = 3; column < ui->gradeTableWidget->columnCount() - 1; ++column){
                        ui->gradeTableWidget->item(row, column)->setText("");
                    }
                }
            }
        }
    } else {

        QMessageBox::warning(this, "경고", "삭제하려는 학생을 먼저 체크해주세요"); //체크된 체크박스가 없다면 경고창을 띄운다
    }
}

void Manager::studentHeaderClicked(int column) {
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

void Manager::gradeHeaderClicked(int column) {
    // 체크박스가 있는 칼럼의 인덱스를 확인합니다.
    int checkboxColumn = 0;

    // 체크박스가 있는 칼럼이 클릭된 경우
    if (column == checkboxColumn) {
        bool allChecked = true;

        // 현재 모든 체크박스의 상태를 확인합니다.
        for (int row = 0; row < ui->gradeTableWidget->rowCount(); ++row) {
            QWidget *widget = ui->gradeTableWidget->cellWidget(row, checkboxColumn);
            if (widget) {
                QCheckBox *checkbox = widget->findChild<QCheckBox *>();
                if (checkbox && !checkbox->isChecked()) {
                    allChecked = false;
                    break;
                }
            }
        }

        // 체크박스의 상태를 반전시킵니다. (모두 선택 or 모두 해제)
        for (int row = 0; row < ui->gradeTableWidget->rowCount(); ++row) {
            QWidget *widget = ui->gradeTableWidget->cellWidget(row, checkboxColumn);
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

    for (int i = 3; i < colCount - 1; ++i) { // 마지막 열 제외
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

void Manager::showHelp(){

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QMessageBox msgBox;
    msgBox.setStyleSheet("QPushButton { width: 10px; height: 5px; }");  // 메시지박스 버튼 크기 조정

    if (button == ui->helppushButton_1) {
        msgBox.setWindowTitle("학생관리탭 도움말");
        msgBox.setText("학생관리 도움말\n\n"
                       "1. 등록 : 오른쪽 테이블에 학생의 정보가 입력됩니다.\n\n"
                       "2. 삭제 : 체크 표시한 학생을 테이블에서 삭제합니다.\n\n"
                       "3. 저장하기 : 해당 테이블을 CSV 파일로 저장합니다.\n\n"
                       "4. 불러오기 : 저장된 CSV 파일을 테이블로 불러옵니다.\n");
    }
    else if(button == ui->helppushButton_2){
        msgBox.setWindowTitle("성적관리탭 도움말");
        msgBox.setText("성적관리 도움말\n\n"
                       "1. 과목추가/삭제 : 테이블에 과목 칼럼을 추가합니다.\n\n"
                       "2. 학생검색 : 입력된 학생을 테이블에서 검색합니다.\n\n"
                       "3. 성적삭제 : 체크된 학생들의 성적을 삭제합니다\n\n"
                       "4. 성적입력 : 테이블에서 직접 성적수정이 가능합니다.\n\n"
                       "4. 입력완료 : 테이블에서 직접 성적수정을 차단합니다.\n\n"
                       "4. 불러오기 : 저장된 테이블 CSV 파일을 불러옵니다.\n\n"
                       "5. 저장하기 : 해당 테이블을 CSV 파일 형식으로 저장합니다.\n");
    }
    else if(button == ui->helppushButton_3){
        msgBox.setWindowTitle("성적표출력탭 도움말");
        msgBox.setText("성적표출력 도움말\n\n"
                       "1. 출력하기 : 프리뷰 테이블 그대로 출력합니다.\n");

    } else {
        msgBox.setWindowTitle("도움말");
        msgBox.setText("각 탭의 도움말 버튼을 클릭하세요.\n");
    }

    msgBox.exec();
}


void Manager::createMenubar() {
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = menuBar->addMenu(tr("&File"));
    QMenu *infoMenu = menuBar->addMenu(tr("&Info"));



    QAction *openAction = new QAction(QIcon("openFile.png"),tr("&Open"), this);
    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setIcon(QIcon(":/icons/openFile.png"));
    connect(openAction, &QAction::triggered, this, &Manager::openStudentFile);
    fileMenu->addAction(openAction);

    fileMenu->addSeparator();

    QAction *saveAction = new QAction(QIcon("saveFile.png"),tr("&Save"), this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setIcon(QIcon(":/icons/saveFile.png"));
    connect(saveAction, &QAction::triggered, this, &Manager::saveStudentFile);
    fileMenu->addAction(saveAction);

    fileMenu->addSeparator();

    QAction *quitAction = new QAction(QIcon("quit.png"),tr("&Quit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setIcon(QIcon(":/icons/quit.png"));
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    fileMenu->addAction(quitAction);

    fileMenu->addSeparator();

    PrintManager *p = new PrintManager;
    QAction *printAction = new QAction(QIcon("print.png"),tr("&Print"), this);
    printAction->setShortcut(tr("Ctrl+P"));
    printAction->setIcon(QIcon(":/icons/print.png"));
    connect(printAction, &QAction::triggered, this, [=](){p->printTable(ui->gradeTableWidget);});
    fileMenu->addAction(printAction);


    QAction *helpAction = new QAction(QIcon("help.png"),tr("&Help"), this);
    helpAction->setShortcut(tr("Ctrl+H"));
    helpAction->setIcon(QIcon(":/icons/help.png"));
    connect(helpAction, &QAction::triggered, this, &Manager::showHelp);
    infoMenu->addAction(helpAction);
}


void Manager::classifySubject(){

    QString currentText = ui->gradecomboBox->currentText(); //콤보박스 현재텍스트 받아옴

    int rowCount = ui->gradeTableWidget->rowCount(); //행수 받아옴
    int columnCount = ui->gradeTableWidget->columnCount(); // 렬수 받아옴

    if(currentText == "전체"){
        for (int row = 0; row < rowCount; ++row){
            ui->gradeTableWidget->setRowHidden(row, false);  //콤보박스가 전체인 경우 행을 하나씩 모두 출력
        }
        for (int column = 0; column < columnCount; ++column){
            ui->gradeTableWidget->setColumnHidden(column, false);  //콤보박스가 전체인 경우 행을 하나씩 모두 출력
        }
    }
    else if(currentText == "문과"){
        for (int row = 0; row < rowCount; ++row) {
            QString id = ui->gradeTableWidget->item(row,1)->text();
            ui->gradeTableWidget->setRowHidden(row, true);
            for (int i = 0; i < studentArtList.size(); i++) {
                if (studentArtList[i]->getId() == id.toInt()) {
                    ui->gradeTableWidget->setRowHidden(row, false);
                    break;
                }
            }
        }

        for (int column = 3; column < columnCount - 1; ++column) {
            QString subject = ui->gradeTableWidget->horizontalHeaderItem(column)->text();
            ui->gradeTableWidget->setColumnHidden(column, true);
            for (int i = 0; i < subjectArtList.size(); i++) {
                if (subjectArtList[i] == subject) {
                    ui->gradeTableWidget->setColumnHidden(column, false);
                    break;
                }
            }
        }
    }
    else if(currentText == "이과"){
        for (int row = 0; row < rowCount; ++row) {
            QString id = ui->gradeTableWidget->item(row,1)->text();
            ui->gradeTableWidget->setRowHidden(row, true);
            for (int i = 0; i < studentSciList.size(); i++) {
                if (studentSciList[i]->getId() == id.toInt()) {
                    ui->gradeTableWidget->setRowHidden(row, false);
                    break;
                }
            }
        }

        for (int column = 3; column < columnCount - 1; ++column) {
            QString subject = ui->gradeTableWidget->horizontalHeaderItem(column)->text();
            ui->gradeTableWidget->setColumnHidden(column, true);
            for (int i = 0; i < subjectSciList.size(); i++) {
                if (subjectSciList[i] == subject) {
                    ui->gradeTableWidget->setColumnHidden(column, false);
                    break;
                }
            }
        }
    }
 }
void Manager::enableTableWidgetEditing(){
    QMessageBox msgBox;
    msgBox.setStyleSheet("QPushButton { width: 1px; height: 1px; }");  // 메시지박스 버튼 크기 조정
    msgBox.setWindowTitle("알림");
    msgBox.setText("이제부터 테이블에서 직접 성적 입력이 가능합니다.\n");
    msgBox.exec();
    ui->gradeTableWidget->setEditTriggers(QAbstractItemView::AllEditTriggers);
}
void Manager::disableTableWidgetEditing(){
    QMessageBox msgBox;
    msgBox.setStyleSheet("QPushButton { width: 1px; height: 1px; }");  // 메시지박스 버튼 크기 조정
    msgBox.setWindowTitle("알림");
    msgBox.setText("이제부터 테이블에서 직접 성적 입력을 차단합니다.\n");
    msgBox.exec();
    ui->gradeTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

