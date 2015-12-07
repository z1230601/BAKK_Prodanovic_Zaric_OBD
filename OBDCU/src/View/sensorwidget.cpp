#include "sensorwidget.h"
#include "ui_sensorwidget.h"

SensorWidget::SensorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SensorWidget)
{
    ui->setupUi(this);
}

SensorWidget::~SensorWidget()
{
    delete ui;
}
