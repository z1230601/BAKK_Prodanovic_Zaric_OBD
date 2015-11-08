#include "Converter.h"

std::string Converter::convertDBEntryToCString(unsigned int index, sql::ResultSet* result) {

	std::string type = result->getMetaData()->getColumnTypeName(index);
	if (type.compare("INT") == 0 ||
			type.compare("INT UNSIGNED") == 0) {
		return std::to_string(result->getInt(index));
	}else if(type.compare("TEXT") == 0){
		return std::string(result->getString(index).asStdString());
	}
	return "";

}
