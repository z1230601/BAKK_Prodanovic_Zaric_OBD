#include "errorpage.h"
#include "ui_errorpage.h"

ErrorPage::ErrorPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorPage)
{
    ui->setupUi(this);
}

ErrorPage::~ErrorPage()
{
    delete ui;
}
