#include "actionsidebar.h"
#include "ui_actionsidebar.h"

ActionSideBar::ActionSideBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionSideBar)
{
    ui->setupUi(this);
}

ActionSideBar::~ActionSideBar()
{
    delete ui;
}
