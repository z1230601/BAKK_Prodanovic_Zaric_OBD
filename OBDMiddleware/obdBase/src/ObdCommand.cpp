#include "ObdCommand.h"
#include "OBDCommandValueFactory.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>

ObdCommand::ObdCommand()
        : pid_(0), description_("")
{
}

ObdCommand::ObdCommand(std::vector<unsigned int> sids, unsigned int pid,
        std::string description)
        : sids_(sids), pid_(pid), description_(description)
{
}

ObdCommand::ObdCommand(std::vector<unsigned int> sids, OBDCommandInput input)
        : sids_(sids), pid_(input.pid_), description_(input.description_)
{
    for(unsigned int i = 0; i < input.values_.size(); i++)
    { //OBDCommandValueInput value : input.values_){
        values_.push_back(
                OBDCommandValueFactory::getInstance()->createOBDValueFromInput(
                        input.values_.at(i), input.validity_mapping_mode_, i));
    }

    is_validity_mapping_active_ = !(input.validity_mapping_mode_ == ValidityMappingMode::OFF);

}

ObdCommand::~ObdCommand()
{
}

void ObdCommand::interpretReceivedBytes(std::vector<uint8_t> data)
{
    if(data.empty())
    {
        return;
    }

    unsigned int total_size = 0;
    for(AbstractOBDValue* value : values_)
    {
        total_size += value->getByteAmount();
    }

    if(is_validity_mapping_active_)
    {
        for(AbstractOBDValue* value : values_)
        {
            value->setValidityByte(data.at(0));
        }

        std::cout << "enter not enterable area" << std::endl;
        data.erase(data.begin());
    }

    if(data.size() == total_size)
    {
        for(unsigned int i = 0, j = 0; i < data.size(); i++)
        {
            std::vector<uint8_t>::const_iterator begins = data.begin() + i;
            std::vector<uint8_t>::const_iterator ends = data.begin() + i
                    + values_.at(j)->getByteAmount();
            std::vector<uint8_t> subdata(begins, ends);
            values_.at(j)->interpretToValue(subdata);
            i += values_.at(j)->getByteAmount() - 1;
            j++;
        }
    }
}

std::vector<uint8_t> ObdCommand::convertToSendableByteArray()
{
    std::vector<uint8_t> ret;
    if(is_validity_mapping_active_)
    {
        uint8_t validity_mapping = 0;
        for(unsigned int i = 0; i < values_.size(); i++)
        {
            uint8_t mask = values_.at(i)->getValidityMask();
            std::cout << "Masking: " << std::hex << (int) validity_mapping << " | " << (int) mask << std::endl << std::dec;
            validity_mapping = validity_mapping | mask;
        }
        ret.push_back(validity_mapping);
    }

    for(AbstractOBDValue* value : values_){
        std::vector<uint8_t> uninterpreted = value->getUninterpretedValueAsVector();
        ret.insert(ret.end(),uninterpreted.begin(), uninterpreted.end());
    }
    return ret;
}

std::string ObdCommand::getRequestString(unsigned int desired_sid)
{
    std::stringstream ret;
    if(std::find(sids_.begin(), sids_.end(), desired_sid) != sids_.end())
    {
        ret << "0" << desired_sid << " " << std::hex << pid_ << std::dec;
    }
    return ret.str();
}

std::vector<unsigned int> ObdCommand::getSids()
{
    return sids_;
}

unsigned int ObdCommand::getPid()
{
    return pid_;
}

std::string ObdCommand::getDescription()
{
    return description_;
}

std::vector<AbstractOBDValue*> ObdCommand::getValues()
{
    return values_;
}
