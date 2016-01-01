#include "AbstractOBDValue.h"

AbstractOBDValue::AbstractOBDValue()
        : name_(""), interpreted_value_(0), byte_amount_(0)
{
}

AbstractOBDValue::AbstractOBDValue(std::string &name,
        unsigned int interpreted_value, unsigned int byte_amount,
        std::vector<uint8_t> &uniterpreted)
        : name_(name), interpreted_value_(interpreted_value), byte_amount_(
                byte_amount), uninterpreted_value_(uniterpreted)
{}

AbstractOBDValue::~AbstractOBDValue()
{}

std::string AbstractOBDValue::getName(){
    return name_;
}

unsigned int AbstractOBDValue::getInterpretedValue(){
    return interpreted_value_;
}

unsigned int AbstractOBDValue::getByteAmount(){
    return byte_amount_;
}

std::vector<uint8_t> AbstractOBDValue::getUninterpretedValue(){
    return uninterpreted_value_;
}
