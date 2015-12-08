#include "abstractobdwidget.h"
#include "actionsidebar.h"

#include <iostream>

AbstractOBDWidget::AbstractOBDWidget(QWidget* parent):
    QWidget(parent)
{
}

QWidget* AbstractOBDWidget::createActionSideBar(QWidget* parent){
    std::cout << "Enter creating SideBar\n";
    sidebar_ = new ActionSideBar(parent);
    return sidebar_;
}
