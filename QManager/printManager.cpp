#include "printManager.h"

#include <QFile>
#include <QPainter>
#include <QTableWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintPreviewWidget>


PrintManager::PrintManager(QObject *parent)
    : QObject(parent) {
}

void PrintManager::printPreviewTable(QTableWidget *tableWidget, QFrame *frame) {
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setFullPage(true); // Use full page for preview

    // Create a print preview widget
    QPrintPreviewWidget *previewWidget = new QPrintPreviewWidget(printer, nullptr);

    // Connect the paintRequested signal to a lambda that performs printing
    connect(previewWidget, &QPrintPreviewWidget::paintRequested, [=]() {
        print(*printer, tableWidget);
        // Render the table widget content to the printer
    });

    // Get the existing layout from the frame
    QLayout *existingLayout = frame->layout();

    // If there is an existing layout, clear it and delete its items
    if (existingLayout) {
        QLayoutItem *item;
        while ((item = existingLayout->takeAt(0)) != nullptr) {
            QWidget *widget = item->widget();
            if (widget) {
                delete widget;
            }
            delete item;
        }
        delete existingLayout;
    }

    QVBoxLayout *layout = new QVBoxLayout(frame);
    frame->setLayout(layout);
    layout->addWidget(previewWidget);
}


void PrintManager::printTable(QTableWidget *tableWidget) {
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, nullptr);

    if (printDialog.exec() == QDialog::Accepted) {
        print(printer, tableWidget);
    }
}


void PrintManager::print(QPrinter &printer, QTableWidget *tableWidget) {

    QPainter painter(&printer);

    // 표의 셀 크기 및 위치 설정
    const int cellWidth = 300;
    const int cellHeight = 100;
    const int tableMargin = 100;
    const int rowSpacing = 0; // 행 간격

    // 페이지의 여백 및 크기 설정
    int pageTop = printer.pageRect(QPrinter::DevicePixel).top();
    int pageBottom = printer.pageRect(QPrinter::DevicePixel).bottom();
    int pageLeft = printer.pageRect(QPrinter::DevicePixel).left();
    int pageRight = printer.pageRect(QPrinter::DevicePixel).right();

    // 현재 페이지의 좌측 상단
    int x = pageLeft + tableMargin;
    int y = pageTop + tableMargin;

    // 테이블 헤더 처리
    QHeaderView *header = tableWidget->horizontalHeader();
    int headerHeight = cellHeight;
    // if (header) {
    //     headerHeight = header->height();
    // }

    // 초기 페이지 시작
    painter.begin(&printer);

    // 테이블 헤더를 페이지 상단에 그립니다.
    int headerY = y;
    if (header) {
        QStringList headerLabels;
        for (int i = 1; i < header->count(); ++i) {
            headerLabels << header->model()->headerData(i, Qt::Horizontal).toString();
        }

        // 헤더 텍스트를 그립니다.
        x = pageLeft + tableMargin; // 페이지 여백으로 x 위치를 초기화합니다.
        for (const QString &label : headerLabels) {
            QRect headerRect(x, headerY, cellWidth, headerHeight);
            painter.drawRect(headerRect);
            painter.drawText(headerRect, Qt::AlignCenter, label);
            x += cellWidth;
        }

        y += headerHeight; // 헤더 높이만큼 y 위치를 이동합니다.
        x = pageLeft + tableMargin;
    }
    // 테이블의 각 행과 열을 읽어 출력
    for (int row = 0; row < tableWidget->rowCount(); ++row) {
        for (int col = 1; col < tableWidget->columnCount(); ++col) {
            QTableWidgetItem *item = tableWidget->item(row, col);
            QString cellText = item ? item->text() : "";

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
            x = pageLeft + tableMargin;
        }
    }

    painter.end();

}
