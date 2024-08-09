#include "manager.h"
#include "./ui_manager.h"

#include <QTextEdit>
#include <QPainter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>

Manager::Manager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Manager)
{
    ui->setupUi(this);
    QString filePathStudent = "C:/Users/change05/Desktop/student.csv";
    QString filePathGrade = "C:/Users/change05/Desktop/grade.csv";
    readStudentFile(filePathStudent);
    readGradeFile(filePathGrade);


    print(filePathGrade);
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

void Manager::print(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::LastEncoding);

    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);

    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);

        // 표의 셀 크기 및 위치 설정
        const int cellWidth = 300;
        const int cellHeight = 100;
        const int tableMargin = 100;
        const int rowSpacing = 0; // 행 간격

        // 현재 페이지의 좌측 상단
        int x = tableMargin;
        int y = tableMargin;

        // 현재 페이지의 여백 설정
        int pageBottom = printer.pageRect(QPrinter::DevicePixel).bottom();
        int pageRight = printer.pageRect(QPrinter::DevicePixel).right();

        // CSV 파일을 행 단위로 읽기
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList cells = line.split(',');

            // 각 셀의 텍스트를 그리기
            for (int col = 0; col < cells.size(); ++col) {
                QString cellText = cells[col];
                QRect cellRect(x, y, cellWidth, cellHeight);

                // 셀 테두리 그리기
                painter.drawRect(cellRect);

                // 셀 텍스트 그리기
                painter.drawText(cellRect, Qt::AlignCenter, cellText);

                // 다음 열로 이동
                x += cellWidth;
            }

            // 다음 행으로 이동
            x = tableMargin;
            y += cellHeight + rowSpacing;

            // 페이지 하단에 도달한 경우 페이지를 넘김
            if (y + cellHeight > pageBottom) {
                painter.end();
                printer.newPage();
                painter.begin(&printer);
                y = tableMargin;
                x = tableMargin;
            }

            // 행이 페이지의 끝에 도달하지 않은 경우, 다음 행으로 이동
            if (x + cellWidth > pageRight) {
                x = tableMargin;
                y += cellHeight + rowSpacing;
            }
        }

        painter.end();
    }
}
