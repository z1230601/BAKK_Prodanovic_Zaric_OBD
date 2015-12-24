#include "ValueElmCommand.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

ValueElmCommand::ValueElmCommand()
{
}

ValueElmCommand::~ValueElmCommand()
{
}

ValueElmCommand::ValueElmCommand(float minReqElmVersion, std::string base_command,
        std::string description, std::string group,
        std::string base_value_format, std::string sub_command,
        std::string sub_value_format)
        : description_(description), group_(group)
{
    base_command_.command_ = base_command;
    base_command_.value_format_ = base_value_format;

    sub_command_.command_ = sub_command;
    sub_command_.value_format_ = sub_value_format;

    if (minReqElmVersion >= 0.0) {
        min_req_version_ = minReqElmVersion;
    }
//    unsigned int bitcount = getBitCount(valueformat);
}

bool ValueElmCommand::valueStringCheckValid(std::string value)
{
    std::transform(value.begin(), value.end(), value.begin(), ::toupper);
    auto newend = std::remove_if(value.begin(), value.end(),
            [](const char & a)->bool
            {
                return !((a >= 48 && a <= 57) || (a >= 65 && a <= 70));
            });
    return newend == value.end();
}

unsigned int ValueElmCommand::getBitCountFromFormat(std::string valueFormat)
{
    unsigned int count = 0;
    for(auto sign : valueFormat)
    {
        if(sign == 'h'
           || sign == 'n'
           || sign == 'x'
           || sign == 'y'
           || sign == 'a'
           || sign == 'b'){
            count += 4;
        }

        if(sign == 'c'){
            count += 8;
        }
    }

    return count;
}

bool ValueElmCommand::checkValueToFormat(std::string value){
    bool length = value.length() == base_command_.value_format_.length();
    bool charplacement = true;
    for(unsigned int i=0; i < value.length(); i++ ){
        if(!(
                (isxdigit(value[i]) && base_command_.value_format_[i] != ' ') ||
                (value[i] == ' ' && base_command_.value_format_[i] == ' ') ||
                (value[i] >= 0x21 && value[i] <= 0x5f && base_command_.value_format_[i] == 'c')
            )
           ){
            charplacement = false;
            break;
        }
    }
    return length && charplacement;
}

float ValueElmCommand::getMinimumRequiredElmVersion() {
    return min_req_version_;
}
std::string ValueElmCommand::getCommand() {
    return base_command_.command_;
}
std::string ValueElmCommand::getDescription() {
    return description_;
}

std::string ValueElmCommand::getGroup() {
    return group_;
}

void ValueElmCommand::setMinimumRequiredElmVersion(float version) {
    if (version >= 0.0) {
        min_req_version_ = version;
    }
}

void ValueElmCommand::setCommand(std::string command) {
    base_command_.command_ = command;
}

void ValueElmCommand::setDescription(std::string description) {
    description_ = description;
}

void ValueElmCommand::setGroup(std::string group) {
    group_ = group;
}
