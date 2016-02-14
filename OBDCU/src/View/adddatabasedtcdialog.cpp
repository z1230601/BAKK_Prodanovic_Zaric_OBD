#include "adddatabasedtcdialog.h"
#include "ui_adddatabasedtcdialog.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <iostream>

AddDatabaseDtcDialog::AddDatabaseDtcDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDatabaseDtcDialog)
{
    ui->setupUi(this);
    QRegExpValidator* code_validator = new QRegExpValidator(QRegExp("[B|C|P|U][0-9A-F]{4}"), this);
    ui->code->setValidator(code_validator);
    ui->code->setPlaceholderText("DTC starting with P,B,C,U");
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
}

void AddDatabaseDtcDialog::on_buttonBox_accepted()
{

    this->setResult(QDialog::Accepted);
}

void AddDatabaseDtcDialog::on_buttonBox_rejected()
{
    this->setResult(QDialog::Rejected);
}
