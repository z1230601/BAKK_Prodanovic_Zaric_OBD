#include "databasewidget.h"
#include "ui_databasewidget.h"

DatabaseWidget::DatabaseWidget(QWidget *parent) :
    AbstractOBDWidget(parent),
    ui(new Ui::DatabaseWidget)
{
    ui->setupUi(this);
}

DatabaseWidget::~DatabaseWidget()
{
    delete ui;
}
