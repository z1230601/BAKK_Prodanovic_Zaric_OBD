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
    if(is_validity_mapping_active_)
    {
        for(AbstractOBDValue* value : values_)
        {
            value->setValidityByte(data.at(0));
            total_size += value->getByteAmount();
        }

        data.erase(data.begin());
    }

    if(data.size() == total_size)
    {
        for(unsigned int i = 0, j = 0; i < data.size(); i++)
        {
            std::vector<uint8_t>::const_iterator begins = data.begin() + i;
            std::vector<uint8_t>::const_iterator ends = data.begin() + i
                    + values_.at(j)->getByteAmount();
            std::vector < uint8_t > subdata(begins, ends);
            values_.at(j)->interpretToValue(subdata);
            i += values_.at(j)->getByteAmount() - 1;
            j++;
        }
    }
}

void ObdCommand::convertToSendableByteArray()
{
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
