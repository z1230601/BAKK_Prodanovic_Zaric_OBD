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
                std::runtime_error("Invalid set option! [Must be true, false or empty string]");
            }
        } catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

OBDBitMappingValue::~OBDBitMappingValue()
{
}

std::string OBDBitMappingValue::interpretToValue(std::vector<uint8_t> input)
{
    std::string ret = "";
    unsigned int key = calculateCompoundValue(input);
    interpreted_value_ = key;
    uninterpreted_value_ = key;
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

std::vector<uint8_t> OBDBitMappingValue::interpretToByteArray(std::string value)
{
    boost::dynamic_bitset<> ret(byte_amount_ * 8);

    std::vector<std::string> splitted;
    boost::split(splitted, value, boost::is_any_of("\n"));

    for(std::string s : splitted)
    {
        if(reverse_true_mapping_.find(s) != reverse_true_mapping_.end())
        {
            unsigned int key = reverse_true_mapping_.at(s);
            if(bit_position_observed_.find(key) != bit_position_observed_.end()
                    && bit_position_observed_.at(key))
            {
                ret.set((size_t) key);
            }
        } else if(reverse_false_mapping_.find(s)
                != reverse_false_mapping_.end())
        {
            unsigned int key = reverse_false_mapping_.at(s);
            if(bit_position_observed_.find(key) != bit_position_observed_.end()
                    && bit_position_observed_.at(key))
            {
                ret.reset((size_t) key);
            }
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

