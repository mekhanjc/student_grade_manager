#include "subjectDialog.h"

SubjectDialog::SubjectDialog(QWidget *parent) : QDialog(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    comboBox = new QComboBox(this);
    comboBox->addItem("공통");
    comboBox->addItem("문과");
    comboBox->addItem("이과");
    layout->addWidget(comboBox);

    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("과목명 : ");
    layout->addWidget(lineEdit);

    QPushButton *okButton = new QPushButton("확인", this);
    QPushButton *cancelButton = new QPushButton("취소", this);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    setLayout(layout);
}

QString SubjectDialog::getSubjectName() const {
    return lineEdit->text();
}

QString SubjectDialog::getSelectedOption() const {
    return comboBox->currentText();
}
