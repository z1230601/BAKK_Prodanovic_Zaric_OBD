#include "databasewidget.h"
#include "ui_databasewidget.h"
#include "../Controller/maincontroller.cpp"
#include "adddatabasedtcdialog.h"
#include <iostream>
#include <utility>

DatabaseWidget::DatabaseWidget(QWidget *parent) :
		AbstractOBDWidget(parent), ui(new Ui::DatabaseWidget) {
	ui->setupUi(this);

	ui->DTCList->setWrapping(true);
	ui->tableSelection->setModel(MainController::getInstance()->getOBDController()->getTableModel());
	MainController::getInstance()->getOBDController()->updateColumnModel(ui->tableSelection->currentText());
	ui->columnSelection->setModel(MainController::getInstance()->getOBDController()->getColumnModel());
	ui->DTCList->setModel(
			MainController::getInstance()->getOBDController()->getDtcListModel());
}

DatabaseWidget::~DatabaseWidget() {
	delete ui;
}

void DatabaseWidget::search(){
    MainController::getInstance()->getOBDController()->searchForDTC(
                ui->tableSelection->currentText(), ui->columnSelection->currentText(), ui->DTCSearchBox->text());
}

void DatabaseWidget::on_DTCSearchButton_clicked() {
    search();
}
void DatabaseWidget::on_DTCSearchBox_returnPressed() {
    search();
}

void DatabaseWidget::on_DTCList_clicked(const QModelIndex &index){
    current_DTC_selected_ = index.data(Qt::DisplayRole).toString();
}

void DatabaseWidget::on_tableSelection_currentIndexChanged(const QString &arg1) {
    MainController::getInstance()->getOBDController()->
            updateColumnModel(ui->tableSelection->currentText());
    ui->columnSelection->setCurrentIndex(0);
}

void DatabaseWidget::on_addDTCButton_clicked()
{
    AddDatabaseDtcDialog dialog(this);
    unsigned int dialog_code = dialog.exec();

    if(dialog_code == QDialog::Accepted)
    {
        MainController::getInstance()->getOBDController()->addDTCToDatabase(dialog.getCode(), dialog.getDescription());
    }
}

void DatabaseWidget::on_removeDTCButton_clicked()
{
    MainController::getInstance()->getOBDController()->removeDTCFromDatabase(current_DTC_selected_);
}

void DatabaseWidget::on_editDTCButton_clicked()
{
    AddDatabaseDtcDialog dialog(this);
    std::pair<QString, QString> values = MainController::getInstance()->getOBDController()->getDTCData(current_DTC_selected_);
    dialog.editValues(values.first, values.second);
    unsigned int dialog_code = dialog.exec();

    if(dialog_code == QDialog::Accepted)
    {
        MainController::getInstance()->getOBDController()->editDTCInDatabase(current_DTC_selected_,dialog.getCode(), dialog.getDescription());
    }
}

void DatabaseWidget::on_configureDatabaseButton_clicked()
{

}
