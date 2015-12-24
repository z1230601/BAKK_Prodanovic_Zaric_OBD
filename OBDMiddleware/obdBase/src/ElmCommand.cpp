#include "ElmCommand.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

ElmCommand::ElmCommand() {
}

ElmCommand::~ElmCommand() {
}

ElmCommand::ElmCommand(float minReqElmVersion,
        std::string base_command, std::string description, std::string group,
        std::string base_value_format, std::string sub_command,
        std::string sub_value_format)
        : description_(description), group_(group)
{
    base_command_.command_ = base_command;
    base_command_.value_format_ = base_value_format;

    sub_command_.command_ = sub_command;
    sub_command_.value_format_ = sub_value_format;

    if(minReqElmVersion >= 1.0) {
        min_req_version_ = minReqElmVersion;
    } else {
        throw std::runtime_error("Invalid Elm Version! Needs to be >= 1.0");
    }
}

bool ElmCommand::isValidValue(std::string value) {
    std::string value_printable(value);

    auto hexend = std::remove_if(value.begin(), value.end(),
            [](const char & a)->bool{return !(isxdigit(a) || isspace(a));});
    bool is_hex = hexend == value.end();

    auto printableend = std::remove_if(value_printable.begin(), value_printable.end(),
                [](const char & a)->bool{return !(a >= 0x21 && a <= 0x5f);});
    bool is_printable = printableend == value_printable.end();

    return is_hex || is_printable;
}

unsigned int ElmCommand::getBitCountFromFormat(std::string valueFormat) {
    unsigned int count = 0;
    for(auto sign : valueFormat) {
        if(sign == 'h' || sign == 'n' || sign == 'x' || sign == 'y'
                || sign == 'a' || sign == 'b') {
            count += 4;
        }

        if(sign == 'c') {
            count += 8;
        }
    }

    return count;
}
bool ElmCommand::checkFormatValue(std::string &value, std::string &format){
    bool length = value.length() == format.length();
        bool charplacement = true;
        for(unsigned int i = 0; i < value.length(); i++) {
            if(!((value[i] >= 0x21 && value[i] <= 0x5f && format[i] == 'c')
                    || (isxdigit(value[i]) && format[i] != ' ')
                    || (value[i] == ' ' && format[i] == ' ')))
            {
                charplacement = false;
                break;
            }
        }
        return length && charplacement;
}

bool ElmCommand::checkBaseValueToFormat(std::string value) {
    return checkFormatValue(value, base_command_.value_format_);
}

bool ElmCommand::checkSubValueToFormat(std::string value){
    return checkFormatValue(value, sub_command_.value_format_);
}

float ElmCommand::getMinimumRequiredElmVersion() {
    return min_req_version_;
}

std::string ElmCommand::getDescription() {
    return description_;
}

std::string ElmCommand::getGroup() {
    return group_;
}

std::string ElmCommand::getCompleteCommandAsString() {
    std::stringstream value_as_string;

    value_as_string << base_command_.command_
            << (base_command_.value_.empty() ? "" : " ") << base_command_.value_
            << (sub_command_.command_.empty() ? "" : " ") << sub_command_.command_
            << (sub_command_.value_.empty() ? "" : " ") << sub_command_.value_;

    return value_as_string.str();
}

void ElmCommand::setBaseValue(std::string value) {
    if(checkBaseValueToFormat(value) && isValidValue(value)) {
        base_command_.value_ = value;
    }
}

void ElmCommand::setSubValue(std::string subvalue) {
    if(checkSubValueToFormat(subvalue) && isValidValue(subvalue)) {
        sub_command_.value_ = subvalue;
    }
}
