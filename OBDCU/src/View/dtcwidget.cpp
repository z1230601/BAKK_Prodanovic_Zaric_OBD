#include "dtcwidget.h"
#include "ui_dtcwidget.h"
#include "../Controller/maincontroller.h"


DTCWidget::DTCWidget(QWidget *parent) :
    AbstractOBDWidget(parent),
    ui(new Ui::DTCWidget)
{
    ui->setupUi(this);
    QStringList list_tables = MainController::getInstance()->getOBDController()->getTableList();
    table_model_ = new QStringListModel();
    table_model_->setStringList(list_tables);
    ui->tableSelection->setModel(table_model_);

    QStringList list_columns = MainController::getInstance()->getOBDController()->
            getColumnList(ui->tableSelection->currentText());
    column_model_ = new QStringListModel();
    column_model_->setStringList(list_columns);
    ui->columnSelection->setModel(column_model_);

    dtc_list_model_ = new QStringListModel();
    ui->DTCList->setModel(dtc_list_model_);
    permanent_list_model_ = new QStringListModel();
    ui->permanentDTCList->setModel(permanent_list_model_);
    pending_list_model_ = new QStringListModel();
    ui->pendingDTCList->setModel(pending_list_model_);
}

DTCWidget::~DTCWidget()
{
    delete ui;
    delete column_model_;
}

void DTCWidget::on_DTCSearchButton_clicked()
{
    search();
}

void DTCWidget::search(){
    QStringList list_search = MainController::getInstance()->getOBDController()->searchModelList(
                ui->tableSelection->currentText(), ui->columnSelection->currentText(), ui->DTCSearchBox->text());
    dtc_list_model_->setStringList(list_search);
}

void DTCWidget::on_DTCSearchBox_returnPressed()
{
    search();
}

void DTCWidget::on_addToPendingButtoon_clicked()
{
}

void DTCWidget::on_removeFromPendingButton_clicked()
{

}

void DTCWidget::on_addToPermanentButton_clicked()
{
    QStringList new_list = MainController::getInstance()->getOBDController()->addToPermanent(current_DTC_selection_);
    permanent_list_model_->setStringList(new_list);
    dtc_list_model_->setStringList(MainController::getInstance()->getOBDController()->getCurrentDTCList());
}

void DTCWidget::on_removeFromPermanentButton_clicked()
{

}

void DTCWidget::on_DTCList_clicked(const QModelIndex &index)
{
    QModelIndexList list = ui->DTCList->selectionModel()->selectedIndexes();
    current_DTC_selection_ = index.data(Qt::DisplayRole).toString();
}
