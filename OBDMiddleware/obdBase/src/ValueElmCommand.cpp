#include "ValueElmCommand.h"
#include "BaseElmCommand.h"

#include <algorithm>
#include <iostream>
#include <sstream>

ValueElmCommand::ValueElmCommand()
{
}

ValueElmCommand::~ValueElmCommand()
{
}

ValueElmCommand::ValueElmCommand(float minReqElmVersion, std::string command,
        std::string value, std::string description, std::string group,
        std::string valueformat)
        : BaseElmCommand(minReqElmVersion, command, description, group),
          value_(value),
          value_format_(valueformat)
{
    std::string valueChecked = valueStringCheckValid(value);
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
    bool length = value.length() == value_format_.length();
    bool charplacement = true;
    for(int i=0; i < value.length(); i++ ){
        if(!((isxdigit(value[i]) && value_format_[i] != ' ') ||
                (value[i] == ' ' && value_format_[i] == ' '))){
            charplacement = false;
            break;
        }
    }
    return length && charplacement;
}
