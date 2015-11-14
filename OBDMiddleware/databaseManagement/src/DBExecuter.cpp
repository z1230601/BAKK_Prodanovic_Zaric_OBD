#include "DBExecuter.h"
#include "SQLStatementFactory.h"
#include <boost/algorithm/string/join.hpp>

DBExecuter::DBExecuter() {

}

DBExecuter::DBExecuter(std::string configuration) {
	database_ = new DBRepresenter(configuration);
}

DBExecuter::~DBExecuter() {
	delete database_;
}

DBRepresenter* DBExecuter::getDatabase(){
	return database_;
}

SQLTable DBExecuter::readData(std::string table, std::vector<std::string> columns, std::string condition){
	database_->connectToDatabase();
	std::string columns_as_string_ = boost::algorithm::join(columns, ", ");
	std::string query = SQLStatementFactory::getInstance()->getStatement("read", table, columns_as_string_, condition);
	SQLTable ret = database_->executeSQLStatement(query);
	database_->closeConnection();
	return ret;
}
