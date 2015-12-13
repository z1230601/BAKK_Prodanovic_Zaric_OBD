/*
 * Configuration.cpp
 *
 *  Created on: Dec 13, 2015
 *      Author: zlatan
 */

#include "Configuration.h"

Configuration* Configuration::instance_;
Configuration::Configuration() {
}

Configuration::~Configuration() {
}

Configuration* Configuration::getInstance(){
	if(instance_ == NULL){
		instance_ = new Configuration();
	}

	return instance_;
}

std::string Configuration::getDatabaseConfigFilePath(){
	return database_path_;
}
void Configuration::setDatabaseConfigFilePath(std::string &path){
	database_path_ = path;
}

