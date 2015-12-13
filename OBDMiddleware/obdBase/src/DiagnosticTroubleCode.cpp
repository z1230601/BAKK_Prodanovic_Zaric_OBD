#include "DiagnosticTroubleCode.h"
#include "../../databaseManagement/src/DBExecuter.h"
#include "Configuration.h"

DiagnosticTroubleCode::DiagnosticTroubleCode() {
	code_class_ = "";
	source_class_ = "";
	description_ = "";
	short_description_ = "";
	code_class_ID_ = -1;
	source_class_ID_ = -1;
	valid_construction_ = false;
}

DiagnosticTroubleCode::DiagnosticTroubleCode(unsigned int code_id,
		unsigned int source_id, std::string &short_description,
		std::string &description) {
	code_class_ID_ = code_id;
	source_class_ID_ = source_id;
	if (!parseClasses(true)) {
		return;
	}
	short_description_ = short_description;
	description_ = description;
	valid_construction_ = true;
}

DiagnosticTroubleCode::DiagnosticTroubleCode(std::string &codeclass,
		std::string &sourceclass, std::string &short_description,
		std::string &description) {
	code_class_ = codeclass;
	source_class_ = sourceclass;
	if (!parseClasses(false)) {
		return;
	}
	short_description_ = short_description;
	description_ = description;
	valid_construction_ = true;
}

DiagnosticTroubleCode::~DiagnosticTroubleCode() {
	// TODO Auto-generated destructor stub
}

bool DiagnosticTroubleCode::parseClasses(bool idMode) {
	DBExecuter exec(Configuration::getInstance()->getDatabaseConfigFilePath());

	if (idMode) {
		std::vector<std::vector<std::string>> readData = exec.readData(
				"CodeClass", std::vector<std::string> { "Property" },
				"ID = \"" + std::to_string(code_class_ID_) + "\"");
		std::cout << "ID = " + std::to_string(code_class_ID_) << " " << readData.size() << " " <<
				readData.at(1).size() << " " << readData.at(1).at(0) << std::endl;
		if (readData.size() == 2 && readData.at(1).size() == 1) {
			code_class_ = std::string(readData.at(1).at(0));
		} else {
			return false;
		}
		readData = exec.readData("Source", std::vector<std::string> { "Name" },
				"ID = \"" + std::to_string(source_class_ID_) + "\"");
		std::cout << "ID = " + std::to_string(source_class_ID_) << " " << readData.size() << " " <<
				readData.at(1).size() << " " << readData.at(1).at(0) << std::endl;
		if (readData.size() == 2 && readData.at(1).size() == 1) {
			source_class_ = std::string(readData.at(1).at(0));
			std::cout << "-----SOURCECLASSE----- : " << source_class_ << std::endl;
		} else {
			return false;
		}
	} else {
		std::vector<std::vector<std::string>> readData = exec.readData(
				"CodeClass", std::vector<std::string> { "ID" },
				"Property = \"" + code_class_ + "\"");
		if (readData.size() >= 2 && readData.at(1).size() == 1) {
			code_class_ID_ = std::stoi(readData.at(1).at(0));
		} else {
			return false;
		}
		readData = exec.readData("Source", std::vector<std::string> { "ID" },
				"Name = \"" + source_class_ + "\"");
		if (readData.size() >= 2 && readData.at(1).size() == 1) {
			source_class_ = std::stoi(readData.at(1).at(0));
		} else {
			return false;
		}
	}
	return true;
}
// GETTER

bool DiagnosticTroubleCode::isValidlyConstructed() {
	return valid_construction_;
}

std::string DiagnosticTroubleCode::getCodeClass() {
	return code_class_;
}

std::string DiagnosticTroubleCode::getSourceClass() {
	return source_class_;
}

std::string DiagnosticTroubleCode::getDescription() {
	return description_;
}

std::string DiagnosticTroubleCode::getShortDescription() {
	return short_description_;
}

unsigned int DiagnosticTroubleCode::getCodeClassID() {
	return code_class_ID_;
}

unsigned int DiagnosticTroubleCode::getSourceClassID() {
	return source_class_ID_;
}
