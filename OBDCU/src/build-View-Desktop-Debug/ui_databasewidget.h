/********************************************************************************
** Form generated from reading UI file 'databasewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEWIDGET_H
#define UI_DATABASEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DatabaseWidget
{
public:

    void setupUi(QWidget *DatabaseWidget)
    {
        if (DatabaseWidget->objectName().isEmpty())
            DatabaseWidget->setObjectName(QStringLiteral("DatabaseWidget"));
        DatabaseWidget->resize(400, 300);

        retranslateUi(DatabaseWidget);

        QMetaObject::connectSlotsByName(DatabaseWidget);
    } // setupUi

    void retranslateUi(QWidget *DatabaseWidget)
    {
        DatabaseWidget->setWindowTitle(QApplication::translate("DatabaseWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class DatabaseWidget: public Ui_DatabaseWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEWIDGET_H
