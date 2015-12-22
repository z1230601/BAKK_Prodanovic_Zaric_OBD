#include "ValueElmCommand.h"
#include "BaseElmCommand.h"

ValueElmCommand::ValueElmCommand() {
}
ValueElmCommand::~ValueElmCommand() {
}

ValueElmCommand::ValueElmCommand(float minReqElmVersion, std::string command,
		unsigned int value, std::string description, std::string group) :
		BaseElmCommand(minReqElmVersion, command, description, group) {
	values_.push_back(value);
}

ValueElmCommand::ValueElmCommand(float minReqElmVersion, std::string command,
		std::vector<unsigned int> values, std::string description,
		std::string group) :
		BaseElmCommand(minReqElmVersion, command, description, group) {
	values_.insert(values_.end(), values.begin(), values.end());
}

uint8_t* ValueElmCommand::getCommandAsByteArray() {
	//TODO: see value types int or byte or hex etc..
	uint8_t* temp_array = (uint8_t*) malloc(
			command_.size() + values_.size() * sizeof(unsigned int)
					+ values_.size() * sizeof(char));

	memcpy(temp_array, command_.c_str(), command_.size());
	return temp_array;
}

unsigned int ValueElmCommand::getSingleValue() {
	if (values_.size() > 0) {
		return values_.at(0);
	}

	throw std::out_of_range("Command Values are empty for " << command_ << ".");
}

