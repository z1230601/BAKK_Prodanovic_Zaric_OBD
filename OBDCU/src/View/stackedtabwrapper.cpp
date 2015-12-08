#include "stackedtabwrapper.h"
#include "ui_stackedtabwrapper.h"
#include "actionsidebar.h"

#include <QEventTransition>

#include <iostream>

StackedTabWrapper::StackedTabWrapper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedTabWrapper)
{
    ui->setupUi(this);
//    ui->actionWidget->stackUnder(ui->mainWidget);
    setupStateMachine();
}

StackedTabWrapper::~StackedTabWrapper()
{
    delete ui;
}

void StackedTabWrapper::setupStateMachine(){

    QState* expanded = new QState();
    QState* folded = new QState();

//    folded->assignProperty(ui->stateLabel, "text", QString("Folded"));
    folded->assignProperty(ui->mainWidget,"enabled", true);
//    folded->assignProperty(ui->mainWidget, "geometry");
    folded->assignProperty(ui->actionWidget,"enabled", false);
    folded->assignProperty(ui->actionWidget, "visible", false);
    folded->assignProperty(ui->mainWidget, "isActiveWindow", true);

//    expanded->assignProperty(ui->stateLabel, "text", QString("Expanded"));
    expanded->assignProperty(ui->mainWidget,"enabled", false);
    expanded->assignProperty(ui->actionWidget,"enabled", true);
    expanded->assignProperty(ui->actionWidget, "visible", true);
    expanded->assignProperty(ui->actionWidget, "isActiveWindow", true);

    folded->connect(folded, SIGNAL(entered()),ui->mainWidget,SLOT(raise()));
    expanded->connect(expanded, SIGNAL(entered()),ui->actionWidget,SLOT(raise()));

    QEventTransition *foldTransition = new QEventTransition(ui->swBtn, QEvent::MouseButtonRelease);
    foldTransition->setTargetState(expanded);
    folded->addTransition(foldTransition);

    QEventTransition *expandTransition = new QEventTransition(ui->swBtn, QEvent::MouseButtonRelease);
    expandTransition->setTargetState(folded);
    expanded->addTransition(expandTransition);

    stateMachine.addState(folded);
    stateMachine.addState(expanded);
    stateMachine.setInitialState(folded);
    stateMachine.start();
}
