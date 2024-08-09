/********************************************************************************
** Form generated from reading UI file 'manager.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Manager
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *Label;
    QLineEdit *LineEditName;
    QLabel *Label_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonMale;
    QRadioButton *radioButtonFemale;
    QLabel *Label_3;
    QLineEdit *LineEditBirth;
    QLabel *Label_4;
    QLineEdit *LineEditPhone;
    QLabel *Label_5;
    QLineEdit *LineEditAddress;
    QLabel *Label_6;
    QComboBox *ComboBoxMajor;
    QTableWidget *tableWidgetStudent;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *deleteButton;
    QPushButton *registButton;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QWidget *tab_2;
    QTableWidget *tableWidgetGrade;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QWidget *tab_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Manager)
    {
        if (Manager->objectName().isEmpty())
            Manager->setObjectName("Manager");
        Manager->resize(800, 600);
        centralwidget = new QWidget(Manager);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(20, 20, 781, 541));
        tab = new QWidget();
        tab->setObjectName("tab");
        formLayoutWidget = new QWidget(tab);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(20, 50, 201, 374));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setVerticalSpacing(40);
        formLayout->setContentsMargins(0, 0, 0, 0);
        Label = new QLabel(formLayoutWidget);
        Label->setObjectName("Label");

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        LineEditName = new QLineEdit(formLayoutWidget);
        LineEditName->setObjectName("LineEditName");

        formLayout->setWidget(0, QFormLayout::FieldRole, LineEditName);

        Label_2 = new QLabel(formLayoutWidget);
        Label_2->setObjectName("Label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        radioButtonMale = new QRadioButton(formLayoutWidget);
        radioButtonMale->setObjectName("radioButtonMale");

        horizontalLayout->addWidget(radioButtonMale);

        radioButtonFemale = new QRadioButton(formLayoutWidget);
        radioButtonFemale->setObjectName("radioButtonFemale");

        horizontalLayout->addWidget(radioButtonFemale);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        Label_3 = new QLabel(formLayoutWidget);
        Label_3->setObjectName("Label_3");

        formLayout->setWidget(3, QFormLayout::LabelRole, Label_3);

        LineEditBirth = new QLineEdit(formLayoutWidget);
        LineEditBirth->setObjectName("LineEditBirth");

        formLayout->setWidget(3, QFormLayout::FieldRole, LineEditBirth);

        Label_4 = new QLabel(formLayoutWidget);
        Label_4->setObjectName("Label_4");

        formLayout->setWidget(4, QFormLayout::LabelRole, Label_4);

        LineEditPhone = new QLineEdit(formLayoutWidget);
        LineEditPhone->setObjectName("LineEditPhone");

        formLayout->setWidget(4, QFormLayout::FieldRole, LineEditPhone);

        Label_5 = new QLabel(formLayoutWidget);
        Label_5->setObjectName("Label_5");

        formLayout->setWidget(5, QFormLayout::LabelRole, Label_5);

        LineEditAddress = new QLineEdit(formLayoutWidget);
        LineEditAddress->setObjectName("LineEditAddress");

        formLayout->setWidget(5, QFormLayout::FieldRole, LineEditAddress);

        Label_6 = new QLabel(formLayoutWidget);
        Label_6->setObjectName("Label_6");

        formLayout->setWidget(2, QFormLayout::LabelRole, Label_6);

        ComboBoxMajor = new QComboBox(formLayoutWidget);
        ComboBoxMajor->setObjectName("ComboBoxMajor");

        formLayout->setWidget(2, QFormLayout::FieldRole, ComboBoxMajor);

        tableWidgetStudent = new QTableWidget(tab);
        if (tableWidgetStudent->columnCount() < 6)
            tableWidgetStudent->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidgetStudent->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidgetStudent->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidgetStudent->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidgetStudent->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidgetStudent->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidgetStudent->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableWidgetStudent->setObjectName("tableWidgetStudent");
        tableWidgetStudent->setGeometry(QRect(230, 20, 531, 471));
        tableWidgetStudent->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidgetStudent->horizontalHeader()->setDefaultSectionSize(80);
        tableWidgetStudent->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidgetStudent->horizontalHeader()->setStretchLastSection(true);
        tableWidgetStudent->verticalHeader()->setVisible(true);
        tableWidgetStudent->verticalHeader()->setCascadingSectionResizes(false);
        tableWidgetStudent->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWidgetStudent->verticalHeader()->setStretchLastSection(false);
        gridLayoutWidget = new QWidget(tab);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(40, 420, 160, 86));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        deleteButton = new QPushButton(gridLayoutWidget);
        deleteButton->setObjectName("deleteButton");

        gridLayout->addWidget(deleteButton, 0, 1, 1, 1);

        registButton = new QPushButton(gridLayoutWidget);
        registButton->setObjectName("registButton");

        gridLayout->addWidget(registButton, 0, 0, 1, 1);

        pushButton_6 = new QPushButton(gridLayoutWidget);
        pushButton_6->setObjectName("pushButton_6");

        gridLayout->addWidget(pushButton_6, 1, 0, 1, 1);

        pushButton_7 = new QPushButton(gridLayoutWidget);
        pushButton_7->setObjectName("pushButton_7");

        gridLayout->addWidget(pushButton_7, 1, 1, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tableWidgetGrade = new QTableWidget(tab_2);
        tableWidgetGrade->setObjectName("tableWidgetGrade");
        tableWidgetGrade->setGeometry(QRect(110, 30, 651, 441));
        tableWidgetGrade->horizontalHeader()->setDefaultSectionSize(75);
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 50, 75, 24));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(20, 80, 75, 24));
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(20, 430, 75, 24));
        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(20, 400, 75, 24));
        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(20, 200, 75, 24));
        pushButton_8 = new QPushButton(tab_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(20, 370, 75, 24));
        pushButton_9 = new QPushButton(tab_2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(20, 230, 75, 24));
        pushButton_10 = new QPushButton(tab_2);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(20, 260, 75, 24));
        tabWidget->addTab(tab_2, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName("tab_5");
        tabWidget->addTab(tab_5, QString());
        Manager->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Manager);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Manager->setMenuBar(menubar);
        statusbar = new QStatusBar(Manager);
        statusbar->setObjectName("statusbar");
        Manager->setStatusBar(statusbar);

        retranslateUi(Manager);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Manager);
    } // setupUi

    void retranslateUi(QMainWindow *Manager)
    {
        Manager->setWindowTitle(QCoreApplication::translate("Manager", "Manager", nullptr));
        Label->setText(QCoreApplication::translate("Manager", "\354\235\264\353\246\204", nullptr));
        Label_2->setText(QCoreApplication::translate("Manager", "\354\204\261\353\263\204", nullptr));
        radioButtonMale->setText(QCoreApplication::translate("Manager", "\353\202\250\354\204\261", nullptr));
        radioButtonFemale->setText(QCoreApplication::translate("Manager", "\354\227\254\354\204\261", nullptr));
        Label_3->setText(QCoreApplication::translate("Manager", "\354\203\235\353\205\204\354\233\224\354\235\274", nullptr));
        Label_4->setText(QCoreApplication::translate("Manager", "\354\240\204\355\231\224\353\262\210\355\230\270", nullptr));
        Label_5->setText(QCoreApplication::translate("Manager", "\354\243\274\354\206\214", nullptr));
        Label_6->setText(QCoreApplication::translate("Manager", "\355\225\231\352\263\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidgetStudent->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Manager", "\354\235\264\353\246\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidgetStudent->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Manager", "\354\204\261\353\263\204", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidgetStudent->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Manager", "\355\225\231\352\263\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidgetStudent->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Manager", "\354\203\235\353\205\204\354\233\224\354\235\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidgetStudent->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Manager", "\354\240\204\355\231\224\353\262\210\355\230\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidgetStudent->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Manager", "\354\243\274\354\206\214", nullptr));
        deleteButton->setText(QCoreApplication::translate("Manager", "\354\210\230\354\240\225", nullptr));
        registButton->setText(QCoreApplication::translate("Manager", "\353\223\261\353\241\235", nullptr));
        pushButton_6->setText(QCoreApplication::translate("Manager", "\353\266\210\353\237\254\354\230\244\352\270\260", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Manager", "\354\240\200\354\236\245\355\225\230\352\270\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("Manager", "\355\225\231\354\203\235 \352\264\200\353\246\254", nullptr));
        pushButton->setText(QCoreApplication::translate("Manager", "\352\263\274\353\252\251 \354\266\224\352\260\200", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Manager", "\352\263\274\353\252\251 \354\202\255\354\240\234", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Manager", "\354\240\200\354\236\245\355\225\230\352\270\260", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Manager", "\353\220\230\353\217\214\353\246\254\352\270\260", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Manager", "\355\225\231\354\203\235 \352\262\200\354\203\211", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Manager", "\353\266\210\353\237\254\354\230\244\352\270\260", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Manager", "\355\225\231\354\203\235 \354\202\255\354\240\234", nullptr));
        pushButton_10->setText(QCoreApplication::translate("Manager", "\354\240\204\354\262\264 \354\202\255\354\240\234", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Manager", "\354\204\261\354\240\201 \352\264\200\353\246\254", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("Manager", "\354\204\261\354\240\201\355\221\234 \354\266\234\353\240\245", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Manager: public Ui_Manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGER_H
