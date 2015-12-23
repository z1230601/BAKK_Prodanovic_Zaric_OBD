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
        : BaseElmCommand(minReqElmVersion, command, description, group)
{
    std::string valueChecked = valueStringCheckAndAlter(value);
    unsigned int bitcount = getBitCount(valueformat);
    value_ = new dynamic_bitset<>(bitcount);

    //off by one
    bitcount--;
    for(auto sign : valueChecked){
        char val = isdigit(sign) ? sign - 48: sign - 55;
        (*value_)[bitcount--]   = ((((val & 0x8) >> 3) & 0x1) == 1);
        (*value_)[bitcount--] = ((((val & 0x4) >> 2) & 0x1) == 1);
        (*value_)[bitcount--] = ((((val & 0x2) >> 1) & 0x1) == 1);
        (*value_)[bitcount--] = ((val & 0x1) == 1);
    }
}

uint8_t* ValueElmCommand::getCommandAsByteArray()
{
	//TODO: see value types int or byte or hex etc..
//	uint8_t* temp_array = (uint8_t*) malloc(
//			command_.size() + values_.size() * sizeof(unsigned int)
//					+ values_.size() * sizeof(char));
//
//	memcpy(temp_array, command_.c_str(), command_.size());
//	return temp_array;
    return nullptr;
}

std::string ValueElmCommand::getValueAsString()
{
    std::stringstream res;
    res << std::hex << std::uppercase << value_->to_ulong();
    return res.str();
}

std::string ValueElmCommand::valueStringCheckAndAlter(std::string value)
{
    std::remove_if(value.begin(), value.end(), isspace);
    std::transform(value.begin(), value.end(), value.begin(), ::toupper);
    auto newend = std::remove_if(value.begin(), value.end(),
            [](const char & a)->bool
            {
                return !((a >= 48 && a <= 57) || (a >= 65 && a <= 70));
            });
    value.erase(newend, value.end());
    return value;
}
unsigned int ValueElmCommand::getBitCount(std::string valueFormat)
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
