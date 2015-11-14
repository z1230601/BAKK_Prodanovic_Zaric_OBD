#include "SQLStatementFactory.h"

SQLStatementFactory* SQLStatementFactory::instance_;

SQLStatementFactory* SQLStatementFactory::getInstance(){
	if(instance_ == NULL){
		instance_ = new SQLStatementFactory();
	}
	return instance_;
}

SQLStatementFactory::SQLStatementFactory(){

}

std::string SQLStatementFactory::getStatement(std::string key, std::string table,
		std::string columns, std::string condition){

	if(commandMap_.find(key) == commandMap_.end()){
		return "";
	}

	return commandMap_.at(key) + " " + columns + " FROM " + table + " WHERE " + condition;
}

