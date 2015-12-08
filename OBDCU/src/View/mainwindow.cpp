#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "homewidget.h"
#include "dtcwidget.h"
#include "emulationwidget.h"
#include "sensorwidget.h"
#include "databasewidget.h"
#include "settingswidget.h"
#include "communicationswidget.h"
#include "stackedtabwrapper.h"

#include <QTabWidget>
#include <QWidget>

#include <utility>

using std::make_pair;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initMap();
    setupContentWindows();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupContentWindows(){
    ui->tabWidget->removeTab(0);

    for(unsigned int i = 0; i < viewMap_.size(); i++){
        std::pair<std::string,QWidget*> it = viewMap_.at(i);
        ui->tabWidget->addTab(it.second, QString(it.first.c_str()));
    }
}

void MainWindow::initMap(){
    viewMap_.push_back(make_pair("HOME",      new StackedTabWrapper(ui->tabWidget)));
    viewMap_.push_back(make_pair("DTC",       new DTCWidget           (ui->tabWidget)));
    viewMap_.push_back(make_pair("EMULATION", new EmulationWidget     (ui->tabWidget)));
    viewMap_.push_back(make_pair("SENSOR",    new SensorWidget        (ui->tabWidget)));
    viewMap_.push_back(make_pair("DATABASE",  new DatabaseWidget      (ui->tabWidget)));
    viewMap_.push_back(make_pair("SETTINGS",  new SettingsWidget      (ui->tabWidget)));
    viewMap_.push_back(make_pair("OBD LOG",   new CommunicationsWidget(ui->tabWidget)));
}
