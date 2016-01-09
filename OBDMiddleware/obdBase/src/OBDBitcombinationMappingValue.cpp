#include "OBDBitcombinationMappingValue.h"
#include "../../configurations/src/OBDCommandInputDefinitions.h"

#include <cmath>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/dynamic_bitset.hpp>
#include <utility>
#include <iomanip>

OBDBitcombinationMappingValue::OBDBitcombinationMappingValue()
{
}

OBDBitcombinationMappingValue::OBDBitcombinationMappingValue(
        unsigned int byte_amount)
        : AbstractOBDValue(byte_amount)
{

}

OBDBitcombinationMappingValue::OBDBitcombinationMappingValue(
        OBDCommandValueInput input, ValidityMappingMode mode)
        : OBDBitcombinationMappingValue(input)
{
    if(mode == ValidityMappingMode::MANUAL)
    {
        for(ValidityBitEntry entry: input.man_validity_entries_){
            uint8_t validity_bit_mask_ = 0x1;
            validity_bit_mask_ = validity_bit_mask_ << std::stoi(entry.content_);
            validity_mask_mapping_[getKeyFromBitPositionString(entry.from_)] = validity_bit_mask_;
        }
    }
}

OBDBitcombinationMappingValue::OBDBitcombinationMappingValue(
        OBDCommandValueInput input)
        : AbstractOBDValue(input.name_, input.bytes_)
{
    double limit = pow(2.0, byte_amount_ * 9) - 1;
    for(MappingEntry entry : input.mapping_)
    {
        unsigned int fromKey = getKeyFromBitPositionString(entry.from_);
        unsigned int setKey = std::stoi(entry.set_, nullptr, 2);
        if(fromKey > limit || setKey > fromKey)
        {
            continue;
        }
        mapping_[fromKey][setKey] = entry.content_;
        reverse_mapping_[fromKey][entry.content_] = setKey;
    }
}

OBDBitcombinationMappingValue::~OBDBitcombinationMappingValue()
{
}

std::string OBDBitcombinationMappingValue::interpretToValue(
        std::vector<uint8_t> input)
{
    std::string ret = "";
    unsigned int value = calculateCompoundValue(input);
    uninterpreted_value_ = value;
    interpreted_value_ = value;
    std::map<unsigned int, bool>::iterator it =
            bitcombination_observed_.begin();
    for(; it != bitcombination_observed_.end(); it++)
    {
        if((*it).second)
        {
            unsigned int fromKey = (*it).first;

            if(mapping_.find(fromKey) == mapping_.end())
                continue;

            unsigned int setKey = fromKey & value;
            unsigned int occurencesOfZero = countOccurencesOfZero(fromKey);
            setKey = (setKey >> occurencesOfZero);

            if(mapping_.at(fromKey).find(setKey) == mapping_.at(fromKey).end())
                continue;

            ret += mapping_.at(fromKey).at(setKey);
            ret += "\n";
        }
    }
    ret = ret.substr(0, ret.size() - 1);
    return ret;
}

std::vector<uint8_t> OBDBitcombinationMappingValue::interpretToByteArray(
        std::string value)
{
    unsigned int result = 0;

    std::vector<std::string> splitted;
    boost::split(splitted, value, boost::is_any_of("\n"));

    unsigned int sizeValidScope = std::count_if(
            bitcombination_observed_.begin(), bitcombination_observed_.end(),
            [](std::pair<unsigned int, bool> a)->bool
            {   return a.second;});

    if(sizeValidScope != splitted.size())
    {
        throw std::runtime_error("Validity and Input do not match in size!");
    }

    unsigned int index = 0;
    std::map<unsigned int, bool>::iterator it =
            bitcombination_observed_.begin();
    for(; it != bitcombination_observed_.end(); it++)
    {
        unsigned int fromKey = (*it).first;
        if(!(*it).second
                || reverse_mapping_.find(fromKey) == reverse_mapping_.end()
                || reverse_mapping_.at(fromKey).find(splitted.at(index))
                        == reverse_mapping_.at(fromKey).end())
        {
            continue;
        }

        unsigned int setKey = reverse_mapping_.at(fromKey).at(
                splitted.at(index));
        unsigned int occurencesZero = countOccurencesOfZero(fromKey);

        result = result | (setKey << occurencesZero);
        index++;
    }

    interpreted_value_ = result;
    uninterpreted_value_ = result;
    return calculateByteArrayFromCompoundValue(result);
}

std::map<unsigned int, std::map<unsigned int, std::string> > OBDBitcombinationMappingValue::getMapping()
{
    return mapping_;
}

unsigned int OBDBitcombinationMappingValue::getKeyFromBitPositionString(
        std::string value)
{
    unsigned int key = 0;
    for(char c : value)
    {
        unsigned int power = std::stoi(&c);
        key += (unsigned int) pow(2.0, power);
    }
    return key;
}

void OBDBitcombinationMappingValue::setBitcombinationScope(
        std::map<unsigned int, bool> valid_scope)
{
    bitcombination_observed_ = valid_scope;
}

void OBDBitcombinationMappingValue::setValidityByte(uint8_t byte)
{
    bitcombination_observed_.clear();
    std::map<unsigned int, uint8_t>::iterator it = validity_mask_mapping_.begin();
    for(; it != validity_mask_mapping_.end(); it++){
        bitcombination_observed_[it->first] = byte & it->second;
    }
}

bool OBDBitcombinationMappingValue::isValueValid()
{
    return true;
}

std::map<unsigned int, bool> OBDBitcombinationMappingValue::getBitcombinationScope()
{
    return bitcombination_observed_;
}

unsigned int OBDBitcombinationMappingValue::countOccurencesOfZero(
        unsigned int value)
{
    unsigned int zeros = 0;
    while((value & 0x1) != 1 && zeros < 32)
    {
        value = value >> 1;
        zeros++;
    }
    return zeros;
}
