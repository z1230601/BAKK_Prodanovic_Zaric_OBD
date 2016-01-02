#include "OBDValueMappingValue.h"
#include <iostream>

OBDValueMappingValue::OBDValueMappingValue()
        : AbstractOBDValue()
{
}

OBDValueMappingValue::OBDValueMappingValue(OBDCommandValueInput input)
        : AbstractOBDValue(input.bytes_)
{
    for(unsigned int i = 0; i < input.mapping_.size(); i++)
    {
        try
        {
            unsigned int key_to_insert = std::stoi(input.mapping_.at(i).from_,
                    nullptr, 16);
            mapping_[key_to_insert] = input.mapping_.at(i).content_;
            reverse_mapping_[input.mapping_.at(i).content_] = key_to_insert;
        } catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

OBDValueMappingValue::OBDValueMappingValue(unsigned int byte_amount,
        std::string &name)
        : AbstractOBDValue(name, byte_amount)
{
}
OBDValueMappingValue::OBDValueMappingValue(unsigned int byte_amount)
        : AbstractOBDValue(byte_amount)
{

}
OBDValueMappingValue::~OBDValueMappingValue()
{
}

std::string OBDValueMappingValue::interpretToValue(std::vector<uint8_t> input)
{

    unsigned int key = calculateCompoundValue(input);
    if(mapping_.find(key) != mapping_.end())
    {
        interpreted_value_ = key;
        uninterpreted_value_  = key;
        return mapping_.at(key);
    }
    return "";
}

std::vector<uint8_t> OBDValueMappingValue::interpretToByteArray(
        std::string value)
{
    if(reverse_mapping_.find(value) != reverse_mapping_.end())
    {
        uninterpreted_value_ = reverse_mapping_.at(value);
        interpreted_value_ = uninterpreted_value_;
        return calculateByteArrayFromCompoundValue(uninterpreted_value_);
    }
    return std::vector<uint8_t> { };
}

std::map<unsigned int, std::string> OBDValueMappingValue::getMapping()
{
    return mapping_;
}
