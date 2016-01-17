#ifndef DTCWIDGET_H
#define DTCWIDGET_H

#include <QWidget>
#include "abstractobdwidget.h"
#include "../Controller/OBDController.h"
#include <QModelIndex>
#include <QDebug>
#include <QStringListModel>

namespace Ui {
class DTCWidget;
}

class DTCWidget : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit DTCWidget(QWidget *parent = 0);
    ~DTCWidget();

private slots:
    void on_DTCSearchButton_clicked();
    void on_DTCSearchBox_returnPressed();
    void on_addToPendingButtoon_clicked();
    void on_removeFromPendingButton_clicked();
    void on_addToPermanentButton_clicked();
    void on_removeFromPermanentButton_clicked();

    void on_DTCList_clicked(const QModelIndex &index);

private:
    Ui::DTCWidget *ui;
    QString current_DTC_selection_;
    QStringListModel* column_model_;
    QStringListModel* table_model_;
    QStringListModel* dtc_list_model_;
    QStringListModel* permanent_list_model_;
    QStringListModel* pending_list_model_;

    void search();
};

#endif // DTCWIDGET_H
