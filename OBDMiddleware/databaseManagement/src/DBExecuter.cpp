#include "DBExecuter.h"
#include <boost/algorithm/string/join.hpp>


DBExecuter::DBExecuter() {
}

DBExecuter::DBExecuter(std::string configuration) {
	database_ = new DBRepresenter(configuration);
}
DBExecuter::DBExecuter(DBRepresenter* representer){
	database_ = representer;
}

DBExecuter::~DBExecuter() {
	delete database_;
}

DBRepresenter* DBExecuter::getDatabase(){
	return database_;
}
void DBExecuter::setDatabase(DBRepresenter* database){
	database_ = database;
}
SQLTable DBExecuter::readData(std::string table, std::vector<std::string> columns, std::string condition){
	database_->connectToDatabase();
	std::string columns_as_string_ = boost::algorithm::join(columns, ", ");
	std::string query = "SELECT " + columns_as_string_ + " FROM " + table + " WHERE " + condition;
	SQLTable ret = database_->executeSQLStatement(query);
	database_->closeConnection();
	return ret;
}
bool DBExecuter::insertData(string table, vector<string> columns,
		SQLTable data) {
	try {
		database_->connectToDatabase();
		std::string columns_as_string_ = boost::algorithm::join(columns, ", ");
		std::string data_values_ = getValuesFromInput(data);
		std::string query = "INSERT INTO " + table + " (" + columns_as_string_
				+ ") VALUES " + data_values_;
		std::cout << "----------" << query << "----------" << std::endl;
		SQLTable ret = database_->executeSQLStatement(query);
		database_->closeConnection();
		return true;
	} catch (sql::SQLException &err) {
		std::cerr << err.what() << std::endl;
		return false;
	}
	return true;
}

std::string DBExecuter::getValuesFromInput(SQLTable data) {
	std::string ret = "";

	for(unsigned int i = 0; i < data.size(); i++) {
		ret += "('";
		ret += boost::algorithm::join(data.at(i), "','");
		ret += "'),";
	}

	ret = ret.substr(0, ret.size() - 1);

	return ret;
}
