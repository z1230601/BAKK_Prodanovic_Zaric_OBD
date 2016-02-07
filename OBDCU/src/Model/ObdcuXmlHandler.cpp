#include "ObdcuXmlHandler.h"
#include "Configuration.h"

ObdcuXmlHandler::ObdcuXmlHandler() {
}

ObdcuXmlHandler::~ObdcuXmlHandler() {
}

void ObdcuXmlHandler::handleNode(xmlpp::Node* node) {
	if(node->get_name().compare(DATABSECONFIG_TAG) == 0){
		std::string path = getTextFromNode(node);
		//TODO: check if path existant
		Configuration::getInstance()->setDatabaseConfigFilePath(path);
	}

	if(node->get_name().compare(OBDCONFIG_TAG) == 0){
		std::string path = getTextFromNode(node);
		//TODO: check if path existant
		Configuration::getInstance()->setOBDCommandConfigFilePath(path);
	}

	if(node->get_name().compare(ELMCONFIG_TAG) == 0){
		std::string path = getTextFromNode(node);
		//TODO: check if path existant
		Configuration::getInstance()->setELMConfigFilePath(path);
	}
}


