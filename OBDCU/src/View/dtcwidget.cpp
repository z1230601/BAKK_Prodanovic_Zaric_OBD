#include "dtcwidget.h"
#include "ui_dtcwidget.h"
#include "../Controller/maincontroller.h"
#include <QErrorMessage>

DTCWidget::DTCWidget(QWidget *parent) :
    AbstractOBDWidget(parent),
    ui(new Ui::DTCWidget)
{
    ui->setupUi(this);

    ui->DTCList->setWrapping(true);
    ui->tableSelection->setModel(MainController::getInstance()->getOBDController()->getTableModel());
    MainController::getInstance()->getOBDController()->
            updateColumnModel(ui->tableSelection->currentText());
    ui->columnSelection->setModel(MainController::getInstance()->getOBDController()->getColumnModel());
    ui->DTCList->setModel(MainController::getInstance()->getOBDController()->getDtcListModel());
    ui->permanentDTCList->setModel(MainController::getInstance()->getOBDController()->getPermanentListModel());
    ui->pendingDTCList->setModel(MainController::getInstance()->getOBDController()->getPendingListModel());

}

DTCWidget::~DTCWidget()
{
    delete ui;
}

void DTCWidget::on_DTCSearchButton_clicked()
{
    search();
}

void DTCWidget::search(){
    MainController::getInstance()->getOBDController()->searchForDTC(
                ui->tableSelection->currentText(), ui->columnSelection->currentText(), ui->DTCSearchBox->text());
}

void DTCWidget::on_DTCSearchBox_returnPressed()
{
    search();
}

void DTCWidget::on_addToPendingButtoon_clicked()
{
    MainController::getInstance()->getOBDController()->addToPending(current_DTC_selection_);
}

void DTCWidget::on_removeFromPendingButton_clicked()
{
    MainController::getInstance()->getOBDController()->removeFromPending(current_pending_DTC_selection_);
}

void DTCWidget::on_addToPermanentButton_clicked()
{
    MainController::getInstance()->getOBDController()->addToPermanent(current_DTC_selection_);
}

void DTCWidget::on_removeFromPermanentButton_clicked()
{
    MainController::getInstance()->getOBDController()->removeFromPermanent(current_permanent_DTC_selection_);
}

void DTCWidget::on_DTCList_clicked(const QModelIndex &index)
{
    current_DTC_selection_ = index.data(Qt::DisplayRole).toString();
}

void DTCWidget::on_permanentDTCList_clicked(const QModelIndex &index)
{
    current_permanent_DTC_selection_ = index.data(Qt::DisplayRole).toString();
}

void DTCWidget::on_pendingDTCList_clicked(const QModelIndex &index)
{
    current_pending_DTC_selection_= index.data(Qt::DisplayRole).toString();
}

void DTCWidget::on_tableSelection_currentIndexChanged(const QString &arg1)
{
    MainController::getInstance()->getOBDController()->
            updateColumnModel(ui->tableSelection->currentText());
    ui->columnSelection->setCurrentIndex(0);
}
