#include "BaseElmCommand.h"

BaseElmCommand::BaseElmCommand() {
	// TODO Auto-generated constructor stub

}

BaseElmCommand::BaseElmCommand(float minReqElmVersion, std::string command,
		std::string description, std::string group) :
		command_(command), description_(description), group_(group) {
	if (minReqElmVersion >= 0.0) {
		min_req_version_ = minReqElmVersion;
	}

}

BaseElmCommand::~BaseElmCommand() {

}

float BaseElmCommand::getMinimumRequiredElmVersion() {
	return min_req_version_;
}
std::string BaseElmCommand::getCommand() {
	return command_;
}
std::string BaseElmCommand::getDescription() {
	return description_;
}

std::string BaseElmCommand::getGroup() {
	return group_;
}

void BaseElmCommand::setMinimumRequiredElmVersion(float version) {
	if (version >= 0.0) {
		min_req_version_ = version;
	}
}

void BaseElmCommand::setCommand(std::string command) {
	command_ = command;
}

void BaseElmCommand::setDescription(std::string description) {
	description_ = description;
}

void BaseElmCommand::setGroup(std::string group) {
	group_ = group;
}

unsigned int BaseElmCommand::getCommandLength() {
	return command_.size();
}
