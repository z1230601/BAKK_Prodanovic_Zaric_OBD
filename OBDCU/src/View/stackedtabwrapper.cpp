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

QString StackedTabWrapper::getTabName() const{
    return tabName_;
}

AbstractOBDWidget* StackedTabWrapper::createWidget(QString widgetId){
    if(widgetId.compare("HOME") == 0){
        return (new HomeWidget(ui->mainWidget));
    }
//    else if(widgetId.compare("DTC") == 0){
//        return new DTCWidget(ui->mainWidget);
//    }else if(widgetId.compare("EMULATION") == 0){
//        return new EmulationWidget(ui->mainWidget);
//    }else if(widgetId.compare("SENSOR") == 0){
//        return new SensorWidget(ui->mainWidget);
//    }else if(widgetId.compare("DATABASE") == 0){
//        return new DatabaseWidget(ui->mainWidget);
//    }else if(widgetId.compare("SETTINGS") == 0){
//        return new SettingsWidget(ui->mainWidget);
//    }else if(widgetId.compare("OBD LOG") == 0){
//        return new CommunicationsWidget(ui->mainWidget);
//    }
    else{
        return NULL; // new ErrorPage(ui->mainWidget);
    }
    return NULL;
}
