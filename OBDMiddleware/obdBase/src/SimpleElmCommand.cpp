#include "SimpleElmCommand.h"
#include <cstring>

SimpleElmCommand::SimpleElmCommand() {
}

SimpleElmCommand::SimpleElmCommand(float minReqElmVersion, std::string command,
		std::string description, std::string group) :
		BaseElmCommand(minReqElmVersion, command, description, group) {

}

SimpleElmCommand::~SimpleElmCommand() {
	// TODO Auto-generated destructor stub
}

uint8_t* SimpleElmCommand::getCommandAsByteArray() {
	uint8_t* temp_array = (uint8_t*) malloc(command_.size());
	memcpy(temp_array, command_.c_str(), command_.size());
	return temp_array;
}
