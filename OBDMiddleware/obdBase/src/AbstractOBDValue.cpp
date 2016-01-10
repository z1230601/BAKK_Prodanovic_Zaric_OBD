#include "AbstractOBDValue.h"
#include <stdexcept>
#include <algorithm>

#include <sstream>
AbstractOBDValue::AbstractOBDValue()
        : name_(""), interpreted_value_(0), byte_amount_(0), uninterpreted_value_(
                0)
{
}

AbstractOBDValue::AbstractOBDValue(std::string &name, double interpreted_value,
        unsigned int byte_amount, unsigned int uninterpreted)
        : name_(name), interpreted_value_(interpreted_value), byte_amount_(
                byte_amount), uninterpreted_value_(uninterpreted)
{
}

AbstractOBDValue::AbstractOBDValue(std::string &name, unsigned int byte_amount)
        : name_(name), interpreted_value_(0), byte_amount_(byte_amount), uninterpreted_value_(
                0)
{
}
AbstractOBDValue::AbstractOBDValue(unsigned int byte_amount)
        : name_(""), interpreted_value_(0), byte_amount_(byte_amount), uninterpreted_value_(
                0)
{

}
AbstractOBDValue::~AbstractOBDValue()
{
}

std::string AbstractOBDValue::getName()
{
    return name_;
}

double AbstractOBDValue::getInterpretedValue()
{
    return interpreted_value_;
}

unsigned int AbstractOBDValue::getByteAmount()
{
    return byte_amount_;
}

unsigned int AbstractOBDValue::getUninterpretedValue()
{
    return uninterpreted_value_;
}

unsigned int AbstractOBDValue::calculateCompoundValue(
        std::vector<uint8_t> input)
{
    if(input.size() < byte_amount_)
    {
        throw std::runtime_error(
                "Input size was smaller than byte amount - not sufficient!\n");
    }

    unsigned int compound_value = 0;

    for(unsigned int i = 0; i < byte_amount_; i++)
    {
        compound_value += input.at(i);

        if(i != byte_amount_ - 1)
        {
            compound_value *= 256;
        }
    }

    return compound_value;
}

std::vector<uint8_t> AbstractOBDValue::calculateByteArrayFromCompoundValue(
        unsigned int input)
{
    std::vector<uint8_t> ret;
    for(unsigned int i = 0; i < byte_amount_; i++)
    {
        if(i != 0)
        {
            input = input / 256;
        }
        ret.push_back(input & 0xFF);

    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

void AbstractOBDValue::setValidityByte(uint8_t byte)
{
    is_valid_ = byte & validity_bit_mask_;
}

bool AbstractOBDValue::isValueValid()
{
    return is_valid_;
}

std::string AbstractOBDValue::getInterpretedValueAsString()
{
    std::stringstream ss;
    ss << interpreted_value_;
    return ss.str();
}

uint8_t AbstractOBDValue::getValidityMask()
{
    return validity_bit_mask_;
}

std::vector<uint8_t> AbstractOBDValue::getUninterpretedValueAsVector()
{
    return calculateByteArrayFromCompoundValue(uninterpreted_value_);
}

void AbstractOBDValue::setValidtyPatternBitPosition(unsigned int pos)
{
    validity_bit_mask_ = 0x1;
    validity_bit_mask_ = validity_bit_mask_ << pos;
}
