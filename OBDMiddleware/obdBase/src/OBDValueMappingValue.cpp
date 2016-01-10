#include "OBDValueMappingValue.h"
#include <iostream>

OBDValueMappingValue::OBDValueMappingValue()
        : AbstractOBDValue()
{
}

OBDValueMappingValue::OBDValueMappingValue(OBDCommandValueInput input)
        : AbstractOBDValue(input.bytes_)
{
    initMapping(input);
}

OBDValueMappingValue::OBDValueMappingValue(OBDCommandValueInput input,
        ValidityMappingMode mode, unsigned int auto_pos)
        : AbstractOBDValue(input.bytes_)
{
    initMapping(input);
    switch(mode)
    {
        case ValidityMappingMode::AUTO:
            setValidtyPatternBitPosition(auto_pos);
            break;
        case ValidityMappingMode::MANUAL:
        {
            if(input.man_validity_entries_.empty())
            {
                throw std::runtime_error(
                        "Manual Validity Mapping mode but no entry found!");
            }
            unsigned int bit_position = std::stoi(
                    input.man_validity_entries_.at(0).content_);
            setValidtyPatternBitPosition(bit_position);
            break;
        }
        case ValidityMappingMode::OFF:
            break;
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
        uninterpreted_value_ = key;
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

std::string OBDValueMappingValue::getInterpretedValueAsString()
{
    if(mapping_.find(interpreted_value_) == mapping_.end())
    {
        return "";
    }
    return mapping_.at(interpreted_value_);
}

void OBDValueMappingValue::initMapping(OBDCommandValueInput input)
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

