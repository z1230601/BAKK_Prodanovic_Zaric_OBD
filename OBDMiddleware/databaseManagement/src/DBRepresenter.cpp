#include "DBRepresenter.h"
#include <iostream>

DBRepresenter::DBRepresenter() {
	valid_construction_ = true;
}

DBRepresenter::DBRepresenter(std::string configurationFile) {
	driver_ = new sql::mysql::MySQL_Driver();
	connection_= NULL;
	valid_construction_ = parseConfigurationFile(configurationFile);
}

DBRepresenter::~DBRepresenter() {

}

bool DBRepresenter::isValid() {
	return valid_construction_;
}

void DBRepresenter::connectToDatabase() {
	try {
		if (connection_ == NULL) {
			connection_ = driver_->connect(host_address_, username_, password_);
		} else if (connection_->isClosed()) {
			delete connection_;
			connection_ = driver_->connect(host_address_, username_, password_);
		}
	} catch (sql::SQLException &exp) {
		std::cout << "Connection couldn't be initializede due to: "
				<< exp.what() << std::endl;
	}
}

void DBRepresenter::closeConnection(){
	connection_->close();
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

	return !host_address_.empty() && !username_.empty();
}

void DBRepresenter::parseNode(xmlpp::Node* node) {
	if(node->get_name().compare(ADDRESS_TAG) == 0) {
		host_address_.append("tcp://");
		host_address_.append(getTextFromNode(node));
		host_address_.append(":3306");
		std::cout << "Host Address: " << host_address_ << std::endl;
	}
	if (node->get_name().compare(USER_TAG) == 0) {
		username_ = getTextFromNode(node);
		std::cout << "user: " << username_ << std::endl;
	}
	if (node->get_name().compare(PASSWORD_TAG) == 0) {
		password_ = getTextFromNode(node);
		std::cout << "pass: " << password_ << std::endl;
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


std::vector<std::string> DBRepresenter::executeSQLStatement(std::string statement){
	sql::Statement* statement_;
	if(!connection_->isClosed()) {
		statement_ = connection_->createStatement();

	}
	std::vector<std::string> result;
	return result;
}
