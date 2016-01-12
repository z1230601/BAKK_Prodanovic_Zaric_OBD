#include "maincontroller.h"

MainController* MainController::instance_;

MainController* MainController::getInstance(){
	if(instance_ == NULL){
		instance_ = new MainController();
	}

	return instance_;
}

OBDCommandController* MainController::commandController() {
	return command_controller_;
}

void MainController::init() {
	Configuration::getInstance()->setDatabaseConfigFilePath("");
	Configuration::getInstance()->setOBDCommandConfigFilePath("");
}

MainController::MainController() {
	command_controller_ = new OBDCommandController();
}

MainController::~MainController() {
}

//void MainController::initDatabase(std::string &configuration_path){
void MainController::initDatabase(){
	db_= new DBExecuter("/home/zlatan/development/bakk/cfg/dbconfiguration.xml");
}

