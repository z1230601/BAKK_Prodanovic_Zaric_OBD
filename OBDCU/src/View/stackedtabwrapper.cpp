#include "stackedtabwrapper.h"
#include "ui_stackedtabwrapper.h"
#include "actionsidebar.h"

#include "homewidget.h"
#include "dtcwidget.h"
#include "emulationwidget.h"
#include "sensorwidget.h"
#include "databasewidget.h"
#include "settingswidget.h"
#include "communicationswidget.h"
#include "errorpage.h"

#include <QEventTransition>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QSignalTransition>

#include <iostream>

StackedTabWrapper::StackedTabWrapper(QString widgetId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackedTabWrapper),
    tabName_(widgetId)
{
    ui->setupUi(this);
    tabContentWidget_ = createWidget(widgetId);
    tabContentWidget_->createActionSideBar(ui->actionWidget);
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

QString StackedTabWrapper::getTabName() const{
    return tabName_;
}

AbstractOBDWidget* StackedTabWrapper::createWidget(QString widgetId){
    if(widgetId.compare("HOME") == 0){
        return (new HomeWidget(ui->mainWidget));
    }else if(widgetId.compare("DTC") == 0){
        return new DTCWidget(ui->mainWidget);
    }else if(widgetId.compare("EMULATION") == 0){
        return new EmulationWidget(ui->mainWidget);
    }else if(widgetId.compare("SENSOR") == 0){
        return new SensorWidget(ui->mainWidget);
    }else if(widgetId.compare("DATABASE") == 0){
        return new DatabaseWidget(ui->mainWidget);
    }else if(widgetId.compare("SETTINGS") == 0){
        return new SettingsWidget(ui->mainWidget);
    }else if(widgetId.compare("OBD LOG") == 0){
        return new CommunicationsWidget(ui->mainWidget);
    }else{
        return new ErrorPage(ui->mainWidget);
    }
}
