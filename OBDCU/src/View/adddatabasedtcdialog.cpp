#include "adddatabasedtcdialog.h"
#include "ui_adddatabasedtcdialog.h"
#include <iostream>

AddDatabaseDtcDialog::AddDatabaseDtcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDatabaseDtcDialog)
{
    ui->setupUi(this);
    is_edit = false;
}

AddDatabaseDtcDialog::~AddDatabaseDtcDialog()
{
    delete ui;
}

QString AddDatabaseDtcDialog::getCode() {
    return ui->code->text();
}

QString AddDatabaseDtcDialog::getDescription() {
    return ui->description->text();
}

void AddDatabaseDtcDialog::editValues(QString code, QString description) {
    ui->code->setText(code);
    ui->description->setText(description);
    is_edit = true;
}

void AddDatabaseDtcDialog::on_buttonBox_accepted()
{
    this->setResult(QDialog::Accepted);
}

void AddDatabaseDtcDialog::on_buttonBox_rejected()
{
    this->setResult(QDialog::Rejected);
}
