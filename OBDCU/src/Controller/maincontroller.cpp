#include "maincontroller.h"
#include "Configuration.h"
#include "XMLReader.h"
#include "../Model/ObdcuXmlHandler.h"
#include <iostream>

MainController* MainController::instance_;

MainController* MainController::getInstance() {
	if (instance_ == NULL) {
		instance_ = new MainController();
	}

	return instance_;
}

OBDController* MainController::getOBDController() {
	return command_controller_;
}

bool MainController::init(std::string configuration_file) {
	ObdcuXmlHandler* handler = new ObdcuXmlHandler();
	XMLReader reader(handler);
	bool success = reader.parseFile(configuration_file);
	std::cout << "Success is " << success << std::endl;

	initDatabase();
	std::cout << "INit of db complete"<< std::endl;

	std::cout << "returning\n";
	communication_controller_ = new CommunicationController();
	command_controller_ = new OBDController();
	command_controller_->init();
	return success;
}

DBExecuter* MainController::getDb() {
	return db_;
}

void MainController::setDb(DBExecuter* db) {
	db_ = db;
}

CommunicationController* MainController::getCommunicationController() {
	return communication_controller_;
}

MainController::MainController() {
}

MainController::~MainController() {
}

void MainController::initDatabase() {
	std::cout << "Init Db: "
			<< Configuration::getInstance()->getDatabaseConfigFilePath()
			<< std::endl;
	db_ = new DBExecuter(
			Configuration::getInstance()->getDatabaseConfigFilePath());
}
