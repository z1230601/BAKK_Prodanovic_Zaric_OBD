#include "OBDController.h"
#include "XMLReader.h"
#include "OBDCommandXMLHandler.h"
#include "Configuration.h"
#include "OBDCommandInputDefinitions.h"
#include "DiagnosticTroubleCode.h"
#include "maincontroller.h"

#include <iostream>
#include <string>

OBDController::OBDController() {
}

OBDController::~OBDController() {
	delete column_model_;
	delete table_model_;
	delete dtc_list_model_;
	delete permanent_list_model_;
	delete pending_list_model_;
}

void OBDController::init() {
	initCommands();
	initViewModels();
}

void OBDController::initViewModels() {
	column_model_ = new QStringListModel();
	table_model_ = new QStringListModel();
	dtc_list_model_ = new QStringListModel();
	permanent_list_model_ = new QStringListModel();
	pending_list_model_ = new QStringListModel();

}

QStringList OBDController::getTableList() {
	std::vector<std::string> list =
			MainController::getInstance()->getDb()->getTablenames();

	QStringList ret;
	for (std::string s : list) {
		ret << QString(s.c_str());
	}

	return ret;
}

void OBDController::updateDTCList() {
	std::map<QString, DiagnosticTroubleCode*>::iterator it =
			current_trouble_codes_.begin();
	QStringList ret;
	for (; it != current_trouble_codes_.end(); it++) {

		if (!inCurrentPermanentCodes((*it).second->toStringForView())
				&& !inCurrentPendingCodes((*it).second->toStringForView())) {
			ret << QString((*it).second->toStringForView().c_str());
		}
	}

	dtc_list_model_->setStringList(ret);
}

void OBDController::updateColumnModel(QString currentInput) {
	columns_.clear();
	QStringList ret;
	std::vector<std::string> columns { "COLUMN_NAME" };
	std::string table = "INFORMATION_SCHEMA.COLUMNS";
	std::string condition = "TABLE_NAME =  '" + currentInput.toStdString()
			+ "'";

	SQLTable readData = MainController::getInstance()->getDb()->readData(table,
			columns, condition);

	for (unsigned int i = 1; i < readData.size(); i++) {
		ret << QString(readData.at(i).at(0).c_str());
		columns_.push_back(readData.at(i).at(0));
	}

	column_model_->setStringList(ret);
}

void OBDController::searchForDTC(QString table, QString column,
		QString currentInput) {
	QStringList ret;
	freeDTC(current_trouble_codes_);
	current_trouble_codes_.clear();

	last_search_ = std::make_tuple(table, column, currentInput);

	std::string condition = column.toStdString() + " LIKE '%"
			+ currentInput.toStdString() + "%'";

	SQLTable readdata = MainController::getInstance()->getDb()->readData(
			table.toStdString(), columns_, condition);

	for (unsigned int i = 1; i < readdata.size(); i++) {
		DiagnosticTroubleCode* current = new DiagnosticTroubleCode(
				table.toStdString(), readdata.at(i).at(1), readdata.at(i).at(2),
				readdata.at(i).at(3), readdata.at(i).at(4), true);

		if (current->isValidlyConstructed()) {

			if (!inCurrentPermanentCodes(current->toStringForView())
					&& !inCurrentPendingCodes(current->toStringForView())) {
				QString entry = QString(current->toStringForView().c_str());
				current_trouble_codes_[entry] = current;
				ret << entry;
			} else {
				delete current;
			}
		}
	}

	dtc_list_model_->setStringList(ret);
}

void OBDController::addToPermanent(QString command) {
	if (current_trouble_codes_.find(command) != current_trouble_codes_.end()) {
		current_permanent_trouble_codes_.push_back(
				current_trouble_codes_.at(command));
		current_trouble_codes_.erase(current_trouble_codes_.find(command));
	}

	updateDTCList();
	updatePermanentModel();
}

void OBDController::removeFromPermanent(QString command) {
	std::string input = command.toStdString();
	std::vector<DiagnosticTroubleCode*>::iterator found = std::find_if(
			current_permanent_trouble_codes_.begin(),
			current_permanent_trouble_codes_.end(),
			[input](DiagnosticTroubleCode* cmp)->bool
			{
				return cmp->toStringForView() == input;
			});

	if (found != current_permanent_trouble_codes_.end()) {
		DiagnosticTroubleCode* foundptr = *found;
		current_permanent_trouble_codes_.erase(found);
		current_trouble_codes_[QString(foundptr->toStringForView().c_str())] =
				foundptr;
	}

	updateDTCList();
	updatePermanentModel();
}

void OBDController::updatePermanentModel() {
	QStringList ret;
	for (DiagnosticTroubleCode* code : current_permanent_trouble_codes_) {
		ret << QString(code->toStringForView().c_str());
	}
	permanent_list_model_->setStringList(ret);
}

void OBDController::addToPending(QString command) {
	if (current_trouble_codes_.find(command) != current_trouble_codes_.end()) {
		current_pending_trouble_codes_.push_back(
				current_trouble_codes_.at(command));
		current_trouble_codes_.erase(current_trouble_codes_.find(command));
	}

	updateDTCList();
	updatePendingModel();
}

void OBDController::removeFromPending(QString command) {
	std::string input = command.toStdString();
	std::vector<DiagnosticTroubleCode*>::iterator found = std::find_if(
			current_pending_trouble_codes_.begin(),
			current_pending_trouble_codes_.end(),
			[input](DiagnosticTroubleCode* cmp)->bool
			{
				return cmp->toStringForView() == input;
			});

	if (found != current_pending_trouble_codes_.end()) {
		DiagnosticTroubleCode* foundptr = *found;
		current_pending_trouble_codes_.erase(found);
		current_trouble_codes_[QString(foundptr->toStringForView().c_str())] =
				foundptr;
	}

	updateDTCList();
	updatePendingModel();
}

void OBDController::updatePendingModel() {
	QStringList ret;
	for (DiagnosticTroubleCode* code : current_pending_trouble_codes_) {
		ret << QString(code->toStringForView().c_str());
	}
	pending_list_model_->setStringList(ret);
}

void OBDController::initCommands() {
	OBDCommandXMLHandler xmlconfiguration;
	XMLReader reader(&xmlconfiguration);
	reader.parseFile(
			Configuration::getInstance()->getOBDCommandConfigFilePath());

	int i = 0;

	for (ServiceModeInput input : xmlconfiguration.getParsedData()) {
		std::vector<ObdCommand*> pids;
		for (OBDCommandInput command : input.commands_) {
			pids.push_back(new ObdCommand(input.sid_, command));

			i++;
		}
		for (unsigned int sid : input.sid_) {
			commands_[sid] = pids;
		}
	}
}

bool OBDController::checkDTCExistence(DiagnosticTroubleCode& DTC_to_add,
		QString code, QString description) {
	if (code.isEmpty()) {
		std::cout << "Empty fields are not valid!" << std::endl;
		return true;
	}

	std::string code_as_string = code.toStdString();
	DTC_to_add = DiagnosticTroubleCode(code_as_string.substr(0, 1),
			code_as_string.substr(1, 1), code_as_string.substr(2, 1),
			code_as_string.substr(3, 2), description.toStdString());

	if (!DTC_to_add.isValidlyConstructed()) {
		std::cout << "Not validly constructed" << std::endl;
		return true;
	}

	if (DTC_to_add.alreadyInDatabase(MainController::getInstance()->getDb())) {
		std::cout << "Already in Database" << std::endl;
		return true;
	}

	return false;
}

bool OBDController::addDTCToDatabase(QString code, QString description) {
	DiagnosticTroubleCode DTC_to_add;

	if (!checkDTCExistence(DTC_to_add, code, description)) {
		DTC_to_add.addToDatabase(MainController::getInstance()->getDb());

		std::cout << "Added to database" << std::endl;
		if (std::get<0>(last_search_) != "") {
			searchForDTC(std::get < 0 > (last_search_),
					std::get < 1 > (last_search_),
					std::get < 2 > (last_search_));
		}
		return true;
	}
	return false;
}

void OBDController::removeDTCFromDatabase(QString actual) {
	if (actual.isEmpty())
		return;

	std::map<QString, DiagnosticTroubleCode*>::iterator it =
			current_trouble_codes_.find(actual);

	if (it != current_trouble_codes_.end()) {
		DiagnosticTroubleCode* to_erase = (*it).second;
		current_trouble_codes_.erase(it);
		to_erase->removeFromDatabase(MainController::getInstance()->getDb());
		delete to_erase;
	}
	updateDTCList();
}

std::pair<QString, QString> OBDController::getDTCData(QString actual) {
	if (actual.isEmpty())
		return std::make_pair("", "");

	std::string code = actual.toStdString().substr(0, 5);
	std::string description = actual.toStdString().substr(6);
	return std::make_pair(QString::fromStdString(code),
			QString::fromStdString(description));
}

void OBDController::editDTCInDatabase(QString actual, QString code,
		QString description) {

	DiagnosticTroubleCode DTC;

	if (!checkDTCExistence(DTC, code, description)) {
		removeDTCFromDatabase(actual);
		addDTCToDatabase(code, description);
	}
}

QStringListModel* OBDController::getColumnModel() const {
	return column_model_;
}

QStringListModel* OBDController::getDtcListModel() const {
	return dtc_list_model_;
}

QStringListModel* OBDController::getPendingListModel() const {
	return pending_list_model_;
}

QStringListModel* OBDController::getPermanentListModel() const {
	return permanent_list_model_;
}

QStringListModel* OBDController::getTableModel() {
	table_model_->setStringList(getTableList());
	return table_model_;
}

void OBDController::freeDTC(std::vector<DiagnosticTroubleCode*> toFree) {
	for (DiagnosticTroubleCode* dtc : toFree) {
		delete dtc;
	}
}

void OBDController::freeDTC(std::map<QString, DiagnosticTroubleCode*> toFree) {
	std::map<QString, DiagnosticTroubleCode*>::iterator it =
			current_trouble_codes_.begin();
	for (; it != current_trouble_codes_.end(); it++) {
		delete (*it).second;
	}
}

bool OBDController::inCurrentPermanentCodes(std::string stringForView) {
	return std::find_if(current_permanent_trouble_codes_.begin(),
			current_permanent_trouble_codes_.end(),
			[stringForView](DiagnosticTroubleCode* cmp)->bool
			{
				return cmp->toStringForView() == stringForView;
			}) != current_permanent_trouble_codes_.end();
}

bool OBDController::inCurrentPendingCodes(std::string stringForView) {
	return std::find_if(current_pending_trouble_codes_.begin(),
			current_pending_trouble_codes_.end(),
			[stringForView](DiagnosticTroubleCode* cmp)->bool
			{
				return cmp->toStringForView() == stringForView;
			}) != current_pending_trouble_codes_.end();
}

