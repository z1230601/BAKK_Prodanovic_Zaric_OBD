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

    void on_permanentDTCList_clicked(const QModelIndex &index);

    void on_pendingDTCList_clicked(const QModelIndex &index);

    void on_tableSelection_currentIndexChanged(const QString &arg1);

private:
    Ui::DTCWidget *ui;
    QString current_DTC_selection_;
    QString current_permanent_DTC_selection_;
    QString current_pending_DTC_selection_;

    void search();
};

#endif // DTCWIDGET_H
