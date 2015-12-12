#include "databasewidget.h"
#include "ui_databasewidget.h"
#include "../Controller/maincontroller.cpp"

DatabaseWidget::DatabaseWidget(QWidget *parent) :
    AbstractOBDWidget(parent),
    ui(new Ui::DatabaseWidget)
{
    ui->setupUi(this);
    MainController::getInstance()->initDatabase();
}

DatabaseWidget::~DatabaseWidget()
{
    delete ui;
}
