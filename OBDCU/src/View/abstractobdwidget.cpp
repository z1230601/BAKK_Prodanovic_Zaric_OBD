#include "abstractobdwidget.h"
#include "actionsidebar.h"

#include <iostream>

AbstractOBDWidget::AbstractOBDWidget(QWidget* parent):
    QWidget(parent)
{
}

QWidget* AbstractOBDWidget::createActionSideBar(QWidget* parent){
    sidebar_ = new ActionSideBar(parent);
    return sidebar_;
}
