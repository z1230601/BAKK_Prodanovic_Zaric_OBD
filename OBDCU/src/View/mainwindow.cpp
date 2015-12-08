#include "mainwindow.h"
#include "ui_mainwindow.h"

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

    for(unsigned int i = 0; i < viewList_.size(); i++){
        ui->tabWidget->addTab(viewList_.at(i),viewList_.at(i)->getTabName());
    }
}

void MainWindow::initMap(){
    viewList_.push_back(new StackedTabWrapper("HOME",ui->tabWidget));
//    viewList_.push_back(new StackedTabWrapper("DTC",ui->tabWidget));
//    viewList_.push_back(new StackedTabWrapper("EMULATION",ui->tabWidget));
//    viewList_.push_back(new StackedTabWrapper("SENSOR",ui->tabWidget));
//    viewList_.push_back(new StackedTabWrapper("DATABASE",ui->tabWidget));
//    viewList_.push_back(new StackedTabWrapper("SETTINGS",ui->tabWidget));
//    viewList_.push_back(new StackedTabWrapper("OBD LOG",ui->tabWidget));
}
