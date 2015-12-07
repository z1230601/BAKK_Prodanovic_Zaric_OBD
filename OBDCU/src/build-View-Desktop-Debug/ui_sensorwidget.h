/********************************************************************************
** Form generated from reading UI file 'sensorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORWIDGET_H
#define UI_SENSORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SensorWidget
{
public:

    void setupUi(QWidget *SensorWidget)
    {
        if (SensorWidget->objectName().isEmpty())
            SensorWidget->setObjectName(QStringLiteral("SensorWidget"));
        SensorWidget->resize(400, 300);

        retranslateUi(SensorWidget);

        QMetaObject::connectSlotsByName(SensorWidget);
    } // setupUi

    void retranslateUi(QWidget *SensorWidget)
    {
        SensorWidget->setWindowTitle(QApplication::translate("SensorWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class SensorWidget: public Ui_SensorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORWIDGET_H
