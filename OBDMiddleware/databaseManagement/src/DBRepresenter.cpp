#include "DBRepresenter.h"
#include <iostream>
#include <exception>
#include "Converter.h"

DBRepresenter::DBRepresenter() {
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

bool DBRepresenter::parseConfigurationFile(std::string configurationFile) {
	xmlpp::DomParser parser;
	parser.set_validate();
	parser.set_substitute_entities(); //We just want the text to be resolved/unescaped automatically.
	parser.parse_file(configurationFile);
	if (parser) {
		const xmlpp::Node* currentNode = parser.get_document()->get_root_node(); //deleted by DomParser.

		xmlpp::Node::NodeList children = currentNode->get_children();
		for(xmlpp::Node::NodeList::iterator it = children.begin(); it != children.end(); ++it) {
			parseNode(*it);
		}
	}

	return !host_address_.empty() && !username_.empty() && !dbname_.empty();
}

void DBRepresenter::parseNode(xmlpp::Node* node) {
	if(node->get_name().compare(ADDRESS_TAG) == 0) {
		host_address_.append("tcp://");
		host_address_.append(getTextFromNode(node));
		host_address_.append(":3306");
	}
	if (node->get_name().compare(USER_TAG) == 0) {
		username_ = getTextFromNode(node);
	}
	if (node->get_name().compare(PASSWORD_TAG) == 0) {
		password_ = getTextFromNode(node);
	}
	if (node->get_name().compare(DBNAME_TAG) == 0) {
		dbname_ = getTextFromNode(node);
	}
}

std::string DBRepresenter::getTextFromNode(xmlpp::Node* node) {
	xmlpp::Node::NodeList text_list = node->get_children();
	if (text_list.size() == 1) {
		xmlpp::TextNode* text =
				dynamic_cast<xmlpp::TextNode*>(*text_list.begin());
		return std::string(text->get_content().c_str());
	}
	return "";
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
