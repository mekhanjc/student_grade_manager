#ifndef SUBJECTDIALOG_H
#define SUBJECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

class SubjectDialog : public QDialog {
    Q_OBJECT

public:
    SubjectDialog(QWidget *parent = nullptr);

    QString getSubjectName() const;
    QString getSelectedOption() const;

private:
    QLineEdit *lineEdit;
    QComboBox *comboBox;
};


#endif // SUBJECTDIALOG_H
