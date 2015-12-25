#include "DBRepresenter.h"
#include <iostream>
#include <exception>
#include "Converter.h"

DBRepresenter::DBRepresenter() {
	//TODO: NOT really nice, is it?
	valid_construction_ = true;
}

DBRepresenter::DBRepresenter(std::string configurationFile) {
	driver_ = new sql::mysql::MySQL_Driver();
	connection_= NULL;
	valid_construction_ = parseConfigurationFile(configurationFile);
}

DBRepresenter::~DBRepresenter() {
	if(connection_ != NULL && !connection_->isClosed())
		closeConnection();

	if(connection_ != NULL)
		delete connection_;

	if(driver_ != NULL)
		delete driver_;
}

bool DBRepresenter::isValid() {
	return valid_construction_;
}

void DBRepresenter::connectToDatabase() {
	checkIfValid();
	try {
		if (connection_ == NULL) {
			connection_ = driver_->connect(host_address_, username_, password_);
			connection_->setSchema(dbname_);
		} else if (connection_->isClosed()) {
			delete connection_;
			connection_ = driver_->connect(host_address_, username_, password_);
			connection_->setSchema(dbname_);
		}
	} catch (sql::SQLException &exp) {
		std::cerr << "Connection couldn't be initialized due to: "
				<< exp.what() << std::endl;
	}
}

void DBRepresenter::closeConnection(){
	if(connection_ != NULL){
		connection_->close();
	}
}

bool DBRepresenter::isConnected() {
	return connection_ != NULL && !connection_->isClosed();
}

std::string DBRepresenter::getHostAddress() const {
	return host_address_;
}

std::string DBRepresenter::getPassword() const {
	return password_;
}

std::string DBRepresenter::getUsername() const {
	return username_;
}

std::string DBRepresenter::getDatabaseName() const {
	return dbname_;
}

SQLTable DBRepresenter::executeSQLStatement(std::string statement){
	checkIfValid();
	SQLTable result;

	sql::Statement* statement_ = NULL;

	if (!connection_->isClosed()) {
		statement_ = connection_->createStatement();
		if (statement.find("SELECT") != std::string::npos) {
			sql::ResultSet* result_;

			result_ = statement_->executeQuery(statement);
			//add header
			result = convertToReadableFormat(result_);

			delete result_;
		} else {
			statement_->execute(statement);
		}
	}

	if(statement_ != NULL){
		delete statement_;
	}

	return result;
}

SQLTable DBRepresenter::convertToReadableFormat(sql::ResultSet* result) {
	SQLTable converted;

	converted.push_back(getResultRowAsVector(result, true));

	while (result->next()) {
		converted.push_back(getResultRowAsVector(result));
	}

	return converted;
}

std::vector<std::string> DBRepresenter::getResultRowAsVector(sql::ResultSet* row, bool header){
	std::vector<std::string> row_vector;
	for (unsigned int i = 1; i <= row->getMetaData()->getColumnCount(); i++) {
		if(!header){
			row_vector.push_back(Converter::convertDBEntryToCString(i, row));
		}else{
			row_vector.push_back(row->getMetaData()->getColumnName(i));
		}
	}
	return row_vector;
}

void DBRepresenter::checkIfValid() {
	if (!valid_construction_) {
		throw std::runtime_error("DBRepresenter not validly initialized");
	}
}
