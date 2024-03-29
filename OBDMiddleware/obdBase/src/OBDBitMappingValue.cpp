#include "OBDBitMappingValue.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset.hpp>

OBDBitMappingValue::OBDBitMappingValue()
{
}

OBDBitMappingValue::OBDBitMappingValue(unsigned int byte_amount)
        : AbstractOBDValue(byte_amount)
{
}

OBDBitMappingValue::OBDBitMappingValue(OBDCommandValueInput input)
        : AbstractOBDValue(input.name_, input.bytes_)
{
    initMapping(input);
}

OBDBitMappingValue::OBDBitMappingValue(OBDCommandValueInput input,
        ValidityMappingMode mode)
        : AbstractOBDValue(input.bytes_)
{
    initMapping(input);
}

OBDBitMappingValue::~OBDBitMappingValue()
{
}

std::string OBDBitMappingValue::interpretToValue(std::vector<uint8_t> input)
{
    interpreted_value_ = calculateCompoundValue(input);
    uninterpreted_value_ = interpreted_value_;
    return getInterpretedValueAsString();
}

std::vector<uint8_t> OBDBitMappingValue::interpretToByteArray(std::string value)
{
    bit_position_observed_.clear();
    boost::dynamic_bitset<> ret(byte_amount_ * 8);

    std::vector<std::string> splitted;
    boost::split(splitted, value, boost::is_any_of("\n"));

    for(std::string s : splitted)
    {
        if(reverse_true_mapping_.find(s) != reverse_true_mapping_.end())
        {
            unsigned int key = reverse_true_mapping_.at(s);
            ret.set((size_t) key);
            bit_position_observed_[key] = true;
        } else if(reverse_false_mapping_.find(s)
                != reverse_false_mapping_.end())
        {
            unsigned int key = reverse_false_mapping_.at(s);
            ret.reset((size_t) key);
            bit_position_observed_[key] = true;
        }
    }

//    std::cout << "bitset looks like this: " << ret << std::endl;
    interpreted_value_ = ret.to_ulong();
    uninterpreted_value_ = ret.to_ulong();
    return calculateByteArrayFromCompoundValue(ret.to_ulong());
}

std::map<unsigned int, std::string> OBDBitMappingValue::getTrueMapping()
{
    return true_mapping_;
}

std::map<unsigned int, std::string> OBDBitMappingValue::getFalseMapping()
{
    return false_mapping_;
}

void OBDBitMappingValue::setBitScope(
        std::map<unsigned int, bool> bit_position_observed)
{
    bit_position_observed_ = bit_position_observed;
}

std::map<unsigned int, bool> OBDBitMappingValue::getBitScope()
{
    return bit_position_observed_;
}

void OBDBitMappingValue::initMapping(OBDCommandValueInput input)
{
    for(unsigned int i = 0; i < input.mapping_.size(); i++)
    {
        try
        {
            unsigned int key_to_insert = std::stoi(input.mapping_.at(i).from_);
            if(input.mapping_.at(i).set_.compare("false") == 0)
            {
                false_mapping_[key_to_insert] = input.mapping_.at(i).content_;
                reverse_false_mapping_[input.mapping_.at(i).content_] =
                        key_to_insert;
            } else if(input.mapping_.at(i).set_.compare("true") == 0
                    || input.mapping_.at(i).set_.empty())
            {
                true_mapping_[key_to_insert] = input.mapping_.at(i).content_;
                reverse_true_mapping_[input.mapping_.at(i).content_] =
                        key_to_insert;
            } else
            {
                std::runtime_error(
                        "Invalid set option! [Must be true, false or empty string]");
            }
        } catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

void OBDBitMappingValue::setValidityByte(uint8_t byte)
{
    bit_position_observed_.clear();

    for(unsigned int i = 0; i < 8; i++)
    {
        bit_position_observed_[i] = (byte >> i) & 0x1;
    }
}

bool OBDBitMappingValue::isValueValid()
{
    //is always valid because bit_position_observed_ is checked in interpretation anyway
    return true;
}

uint8_t OBDBitMappingValue::getValidityMask()
{
    unsigned int ret = 0;
    std::map<unsigned int, bool>::iterator it = bit_position_observed_.begin();
    for(; it != bit_position_observed_.end(); it++)
    {
        unsigned int actual = it->second ? 1 : 0;
        actual = actual << it->first;
        ret = ret | actual;
    }
    return ret;
}

std::string OBDBitMappingValue::getInterpretedValueAsString()
{
    std::string ret;
    unsigned int key = interpreted_value_;
    for(unsigned int i = 0; i < byte_amount_ * 8; i++)
    {
        if(bit_position_observed_.find(i) == bit_position_observed_.end()
                || !bit_position_observed_.at(i))
        {
            key = key >> 1;
            continue;
        }
        bool map_choose = key & 0x1;
        key = key >> 1;
        if(map_choose && true_mapping_.find(i) != true_mapping_.end())
        {
            ret += true_mapping_.at(i);
            ret += "\n";
        } else if(!map_choose && false_mapping_.find(i) != false_mapping_.end())
        {
            ret += false_mapping_.at(i);
            ret += "\n";
        }
    }

    ret = ret.substr(0, ret.size() - 1);
    return ret;
}
