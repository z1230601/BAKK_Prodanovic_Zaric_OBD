#include "DiagnosticTroubleCode.h"
#include "../../databaseManagement/src/DBExecuter.h"
#include "Configuration.h"

DiagnosticTroubleCode::DiagnosticTroubleCode() :
		code_class_(""),
		source_class_(""),
		description_(""),
		code_class_ID_(-1),
		source_class_ID_(-1),
		fault_ID_(-1),
		valid_construction_(false) {

}

DiagnosticTroubleCode::DiagnosticTroubleCode(unsigned int code_id,
		unsigned int source_id, std::string &description) :
		description_(description),
		code_class_ID_(code_id),
		source_class_ID_(source_id)
		//TODO: fault_ID_();
		 {

	if (!parseClasses(true)) {
		return;
	}

	valid_construction_ = true;
}

DiagnosticTroubleCode::DiagnosticTroubleCode(std::string &codeclass,
		std::string &sourceclass, std::string &description) :
		code_class_(codeclass),
		source_class_(sourceclass),
		description_(description)
		{

	if (!parseClasses(false)) {
		return;
	}

	valid_construction_ = true;
}

DiagnosticTroubleCode::~DiagnosticTroubleCode() {
	// TODO Auto-generated destructor stub
}

bool DiagnosticTroubleCode::parseClasses(bool idMode) {
	if (idMode) {
		code_class_ = getStringFromIdDB("CodeClass", std::vector<std::string> { "Property" }, "ID = \"" + std::to_string(code_class_ID_) + "\"");
		source_class_ = getStringFromIdDB("Source", std::vector<std::string> { "Name" },
				"ID = \"" + std::to_string(source_class_ID_) + "\"");

		if(source_class_.empty() || code_class_.empty()){
			return false;
		}
	} else {
		code_class_ID_ = getIdFromStringDB("CodeClass", std::vector<std::string> { "ID" },
				"Property = \"" + code_class_ + "\"");

		source_class_ID_ = getIdFromStringDB("Source", std::vector<std::string> { "ID" },
				"Name = \"" + source_class_ + "\"");
		if(code_class_ID_ == (unsigned int) -1 ||
				source_class_ID_ == (unsigned int) -1){
			return false;
		}
	}
	return true;
}

std::string DiagnosticTroubleCode::getStringFromIdDB(std::string tablename,
		std::vector<std::string> columnnames, std::string condition) {
	DBExecuter exec(Configuration::getInstance()->getDatabaseConfigFilePath());
	std::vector<std::vector<std::string>> readData = exec.readData(tablename,
			columnnames, condition);

	if (readData.size() == 2 && readData.at(1).size() == 1) {
		return std::string(readData.at(1).at(0));

	} else {
		return "";
	}
}
unsigned int DiagnosticTroubleCode::getIdFromStringDB(std::string tablename,
		std::vector<std::string> columnnames, std::string condition) {
	DBExecuter exec(Configuration::getInstance()->getDatabaseConfigFilePath());
	std::vector<std::vector<std::string>> readData = exec.readData(tablename, columnnames, condition);
	if (readData.size() >= 2 && readData.at(1).size() == 1) {
		return std::stoi(readData.at(1).at(0));
	} else {
		return -1;
	}
}

unsigned int DiagnosticTroubleCode::idsFromHexValue(unsigned int hexvalue, unsigned int id_position) {
	unsigned int bitmask = 0xF << (id_position * (HEX_LENGTH));
	if(id_position <= 1) {
		bitmask |= 0xF;
		id_position = 0;
	}
	return ((hexvalue & bitmask) >> (id_position * (HEX_LENGTH)));
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

unsigned int DiagnosticTroubleCode::getCodeClassID() {
	return code_class_ID_;
}

unsigned int DiagnosticTroubleCode::getSourceClassID() {
	return source_class_ID_;
}

unsigned int DiagnosticTroubleCode::getFaultID() {
	return fault_ID_;
}

void DiagnosticTroubleCode::fromElmHexValue(int hexvalue) {
	code_class_ID_ = idsFromHexValue(hexvalue, 3);
	source_class_ID_ = idsFromHexValue(hexvalue, 2);
	fault_ID_ = idsFromHexValue(hexvalue, 1);

	valid_construction_ = true;
}

unsigned int DiagnosticTroubleCode::toElmHexValue() {
	return (((code_class_ID_ << (3*HEX_LENGTH)) | (source_class_ID_ << (2*HEX_LENGTH))) | fault_ID_);
}