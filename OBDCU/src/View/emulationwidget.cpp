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
    MainController::getInstance()->getCommunicationController()->initLanguage(ui->langSelector);
    MainController::getInstance()->getCommunicationController()->initDescriptors(ui->manStringInput, ui->productStringInput, ui->serialStringInput);
}

void EmulationWidget::on_saveBtn_clicked()
{
    MainController::getInstance()->getCommunicationController()->saveSettings(ui->elmCfgInput->text(),
                                                                              ui->langSelector->currentText(),
                                                                              ui->manStringInput->text(),
                                                                              ui->productStringInput->text(),
                                                                              ui->serialStringInput->text());
}

void EmulationWidget::on_runBtn_clicked()
{
    std::cout << "run clicked\n";
    MainController::getInstance()->getCommunicationController()->runEmulation();
}

void EmulationWidget::on_stopBtn_clicked()
{
    std::cout << "Stop clicked\n";
    MainController::getInstance()->getCommunicationController()->stopEmulation();
}
