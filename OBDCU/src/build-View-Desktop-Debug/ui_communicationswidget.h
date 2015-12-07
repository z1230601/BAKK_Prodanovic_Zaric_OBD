/********************************************************************************
** Form generated from reading UI file 'communicationswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMUNICATIONSWIDGET_H
#define UI_COMMUNICATIONSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CommunicationsWidget
{
public:

    void setupUi(QWidget *CommunicationsWidget)
    {
        if (CommunicationsWidget->objectName().isEmpty())
            CommunicationsWidget->setObjectName(QStringLiteral("CommunicationsWidget"));
        CommunicationsWidget->resize(400, 300);

        retranslateUi(CommunicationsWidget);

        QMetaObject::connectSlotsByName(CommunicationsWidget);
    } // setupUi

    void retranslateUi(QWidget *CommunicationsWidget)
    {
        CommunicationsWidget->setWindowTitle(QApplication::translate("CommunicationsWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class CommunicationsWidget: public Ui_CommunicationsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNICATIONSWIDGET_H
