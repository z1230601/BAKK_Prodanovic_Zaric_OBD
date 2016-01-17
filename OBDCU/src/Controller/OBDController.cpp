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
}

void OBDController::init() {
	initCommands();
}

QStringList OBDController::getTableList() {
	std::cout << "Enter gettable db is: "
			<< (MainController::getInstance()->getDb() == nullptr) << std::endl;

	std::vector < std::string > list =
			MainController::getInstance()->getDb()->getTablenames();

	QStringList ret;
	for (std::string s : list) {
		ret << QString(s.c_str());
		std::cout << "GOT tableNames: " << s << std::endl;
	}

	return ret;
}

QStringList OBDController::getColumnList(QString currentInput) {
	QStringList ret;
	std::vector < std::string > columns { "COLUMN_NAME" };
	std::string table = "INFORMATION_SCHEMA.COLUMNS";
	std::string condition = "TABLE_NAME =  'Powertrain'";

	SQLTable readData = MainController::getInstance()->getDb()->readData(table,
			columns, condition);

	for (unsigned int i = 1; i < readData.size(); i++) {
		ret << QString(readData.at(i).at(0).c_str());
		columns_.push_back(readData.at(i).at(0));
	}

	return ret;
}

QStringList OBDController::searchModelList(QString table, QString column,
		QString currentInput) {
	QStringList ret;
	freeDTC(current_trouble_codes_);
	current_trouble_codes_.clear();

	std::string condition = column.toStdString() + " LIKE '%"
			+ currentInput.toStdString() + "%'";

	SQLTable readdata = MainController::getInstance()->getDb()->readData(
			table.toStdString(), columns_, condition);

	std::cout << "Size of return: " << readdata.size() << std::endl;
	for (unsigned int i = 1; i < readdata.size(); i++) {
		DiagnosticTroubleCode * current = new DiagnosticTroubleCode(
				table.toStdString(), readdata.at(i).at(1), readdata.at(i).at(2),
				readdata.at(i).at(3), readdata.at(i).at(4));
		if (current->isValidlyConstructed()) {
			QString entry = QString(current->toStringForView().c_str());
			current_trouble_codes_[entry] = current;
			ret << entry;
		}
	}

	return ret;
}

QStringList OBDController::addToPermanent(QString command) {
	if(current_trouble_codes_.find(command)!= current_trouble_codes_.end()){
		current_permanent_trouble_codes_.push_back(current_trouble_codes_.at(command));
		current_trouble_codes_.erase(current_trouble_codes_.find(command));
	}
	QStringList ret;
	for(DiagnosticTroubleCode* code: current_permanent_trouble_codes_){
		ret << QString(code->toStringForView().c_str());
	}
	return ret;
}

QStringList OBDController::getCurrentDTCList() {
	QStringList ret;
	std::map<QString, DiagnosticTroubleCode*>::iterator it = current_trouble_codes_.begin();
	for(; it != current_trouble_codes_.end(); it++){
		ret << QString((*it).second->toStringForView().c_str());
	}
	return ret;
}

void OBDController::initCommands() {
	OBDCommandXMLHandler xmlconfiguration;
	XMLReader reader(&xmlconfiguration);
	std::cout << "parsing file: "
			<< Configuration::getInstance()->getOBDCommandConfigFilePath()
			<< std::endl;
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
	std::cout << "Parsed commands: " << i << std::endl;
}

void OBDController::freeDTC(std::vector<DiagnosticTroubleCode*> toFree) {
	for(DiagnosticTroubleCode* dtc: toFree){
		delete dtc;
	}
}

void OBDController::freeDTC(std::map<QString, DiagnosticTroubleCode*> toFree) {
	std::map<QString, DiagnosticTroubleCode*>::iterator it = current_trouble_codes_.begin();
	for(; it != current_trouble_codes_.end(); it++){
		delete (*it).second;
	}
}
