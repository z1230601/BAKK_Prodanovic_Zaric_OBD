#include "dtcwidget.h"
#include "ui_dtcwidget.h"

DTCWidget::DTCWidget(QWidget *parent) :
    AbstractOBDWidget(parent),
    ui(new Ui::DTCWidget)
{
    ui->setupUi(this);
}

DTCWidget::~DTCWidget()
{
    delete ui;
}
