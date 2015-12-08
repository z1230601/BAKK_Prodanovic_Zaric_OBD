#include "stackedtabwrapper.h"
#include "ui_stackedtabwrapper.h"
#include "actionsidebar.h"

#include <QEventTransition>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QSignalTransition>

#include <iostream>

StackedTabWrapper::StackedTabWrapper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedTabWrapper)
{
    ui->setupUi(this);
    setupStateMachine();
}

StackedTabWrapper::~StackedTabWrapper()
{
    delete ui;
}

void StackedTabWrapper::setupStateMachine() {
    QState* expanded = new QState();
    QState* folded = new QState();

    folded->assignProperty(ui->mainWidget, "enabled", true);
    folded->assignProperty(ui->actionWidget, "enabled", false);
    folded->assignProperty(ui->actionWidget, "visible", false);
    folded->assignProperty(ui->actionWidget, "geometry", QRectF(10, 40, 10, height()));
    folded->connect(folded, SIGNAL(entered()), ui->mainWidget, SLOT(raise()));

    expanded->assignProperty(ui->mainWidget, "enabled", false);
    expanded->assignProperty(ui->actionWidget, "enabled", true);
    expanded->assignProperty(ui->actionWidget, "visible", true);
    expanded->assignProperty(ui->actionWidget, "geometry", QRectF(10, 40, width()/5, height()));
    expanded->assignProperty(ui->actionWidget, "autoFillBackground", true);
    expanded->connect(expanded, SIGNAL(entered()), ui->actionWidget, SLOT(raise()));

    QAbstractTransition* tFoldToExpand = folded->addTransition(ui->swBtn, SIGNAL(clicked()), expanded);
    QSequentialAnimationGroup* animationFoldToExpand = new QSequentialAnimationGroup;
    animationFoldToExpand->addPause(1000);

    tFoldToExpand->addAnimation(animationFoldToExpand);
    tFoldToExpand->addAnimation(new QPropertyAnimation(ui->actionWidget, "geometry"));
    tFoldToExpand->addAnimation(new QPropertyAnimation(ui->mainWidget, "geometry"));

    QAbstractTransition* tExpandToFold = expanded->addTransition(ui->swBtn, SIGNAL(clicked()), folded);
    QSequentialAnimationGroup* animationExpandToFold = new QSequentialAnimationGroup;
    animationExpandToFold->addPause(1000);

    tExpandToFold->addAnimation(animationExpandToFold);
    tExpandToFold->addAnimation(new QPropertyAnimation(ui->actionWidget, "geometry"));
    tExpandToFold->addAnimation(new QPropertyAnimation(ui->mainWidget, "geometry"));

    stateMachine.addState(folded);
    stateMachine.addState(expanded);
    stateMachine.setInitialState(folded);
    stateMachine.start();
}
