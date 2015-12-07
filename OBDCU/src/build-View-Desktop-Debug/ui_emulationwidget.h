/********************************************************************************
** Form generated from reading UI file 'emulationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMULATIONWIDGET_H
#define UI_EMULATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmulationWidget
{
public:

    void setupUi(QWidget *EmulationWidget)
    {
        if (EmulationWidget->objectName().isEmpty())
            EmulationWidget->setObjectName(QStringLiteral("EmulationWidget"));
        EmulationWidget->resize(400, 300);

        retranslateUi(EmulationWidget);

        QMetaObject::connectSlotsByName(EmulationWidget);
    } // setupUi

    void retranslateUi(QWidget *EmulationWidget)
    {
        EmulationWidget->setWindowTitle(QApplication::translate("EmulationWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class EmulationWidget: public Ui_EmulationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMULATIONWIDGET_H
