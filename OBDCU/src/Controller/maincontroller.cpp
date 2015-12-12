/*
 * maincontroller.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: zlatan
 */

#include "maincontroller.h"
#include "databaseManagement/DBExecuter.h"

MainController* MainController::instance_;

MainController* MainController::getInstance(){
	if(instance_ == NULL){
		this instance_ = new MainController();
	}

	return instance_;
}

MainController::MainController() {
}

MainController::~MainController() {
}

void MainController::initDatabase(std::string &configuration_path){
	db_= new DBExecuter(configuration_path);
}

