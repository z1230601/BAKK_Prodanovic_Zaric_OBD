#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include "abstractobdwidget.h"
#include "../Controller/OBDController.h"
#include <QModelIndex>
#include <QDebug>
#include <QStringListModel>

namespace Ui {
class DatabaseWidget;
}

class DatabaseWidget : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit DatabaseWidget(QWidget *parent = 0);
    ~DatabaseWidget();

private slots:
    void on_DTCSearchButton_clicked();
    void on_DTCSearchBox_returnPressed();

    void on_DTCList_clicked(const QModelIndex &index);

    void on_tableSelection_currentIndexChanged(const QString &arg1);

    void on_addDTCButton_clicked();

    void on_removeDTCButton_clicked();

    void on_editDTCButton_clicked();

private:
    Ui::DatabaseWidget *ui;
    QString current_DTC_selected_;

    void search();
};

#endif // DATABASEWIDGET_H
