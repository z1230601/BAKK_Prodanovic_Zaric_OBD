/********************************************************************************
** Form generated from reading UI file 'dtcwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DTCWIDGET_H
#define UI_DTCWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DTCWidget
{
public:

    void setupUi(QWidget *DTCWidget)
    {
        if (DTCWidget->objectName().isEmpty())
            DTCWidget->setObjectName(QStringLiteral("DTCWidget"));
        DTCWidget->resize(400, 300);

        retranslateUi(DTCWidget);

        QMetaObject::connectSlotsByName(DTCWidget);
    } // setupUi

    void retranslateUi(QWidget *DTCWidget)
    {
        DTCWidget->setWindowTitle(QApplication::translate("DTCWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class DTCWidget: public Ui_DTCWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DTCWIDGET_H
