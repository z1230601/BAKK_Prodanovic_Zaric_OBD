#include "homewidget.h"
#include "ui_homewidget.h"

#include "actionsidebar.h"
#include <iostream>

HomeWidget::HomeWidget(QWidget *parent) :
    AbstractOBDWidget(parent),
    ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
}

HomeWidget::~HomeWidget()
{
    delete ui;
}
QWidget* HomeWidget::createActionSideBar(QWidget* parent){
    std::cout << "Home Widget actionbar\n";
    sidebar_ = new ActionSideBar(parent);
    return sidebar_;
}
