#include "databasewidget.h"
#include "ui_databasewidget.h"

DatabaseWidget::DatabaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseWidget)
{
    ui->setupUi(this);
}

DatabaseWidget::~DatabaseWidget()
{
    delete ui;
}
