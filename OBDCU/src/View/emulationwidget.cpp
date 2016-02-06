#include "emulationwidget.h"
#include "ui_emulationwidget.h"
#include "../Controller/maincontroller.h"

EmulationWidget::EmulationWidget(QWidget *parent) :
    AbstractOBDWidget(parent),
    ui(new Ui::EmulationWidget)
{
    ui->setupUi(this);
    fillDataFromModel();
}

EmulationWidget::~EmulationWidget()
{
    delete ui;
}

void EmulationWidget::fillDataFromModel(){
    MainController::getInstance()->getCommunicationController()->initConfigurationPath(ui->elmCfgInput);
    MainController::getInstance()->getCommunicationController()->initLaguage(ui->langSelector);
    MainController::getInstance()->getCommunicationController()->initDescriptors(ui->manStringInput, ui->productStringInput, ui->serialStringInput);
}
