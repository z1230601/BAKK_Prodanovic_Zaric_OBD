#include "emulationwidget.h"
#include "ui_emulationwidget.h"

EmulationWidget::EmulationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmulationWidget)
{
    ui->setupUi(this);
}

EmulationWidget::~EmulationWidget()
{
    delete ui;
}
