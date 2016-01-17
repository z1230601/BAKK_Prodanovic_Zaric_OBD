#include "maincontroller.h"
#include "Configuration.h"
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

void MainController::init() {
	Configuration::getInstance()->setDatabaseConfigFilePath(
			"/home/zlatan/development/bakk/cfg/dbconfiguration.xml");
	Configuration::getInstance()->setOBDCommandConfigFilePath(
			"/home/zlatan/development/bakk/cfg/obdcommand.xml");

	command_controller_->init();
}

DBExecuter* MainController::getDb() {
	return db_;
}

void MainController::setDb(DBExecuter* db) {
		db_ = db;
}

MainController::MainController() {
	command_controller_ = new OBDController();
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
