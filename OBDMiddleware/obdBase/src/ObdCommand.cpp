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

void ObdCommand::interpretReceivedBytes(uint8_t data[])
{
    std::vector<uint8_t> data_vector(data, data + sizeof(data) / sizeof(data[0]));
    std::cout << "size: " << data_vector.size() << std::endl;
    for(auto data: data)
    if(data_vector.empty()){
        return;
    }

    if(is_validity_mapping_active_){
        for(AbstractOBDValue* value: values_){
            value->setValidityByte(data_vector.at(0));
        }

        data_vector.erase(data_vector.begin());
    }

    for(unsigned int i=0; i < data_vector.size(); i += values_.at(i)->getByteAmount()){
        std::vector<uint8_t>::const_iterator begins = data_vector.begin() + i;
        std::vector<uint8_t>::const_iterator ends = data_vector.begin() + i + values_.at(i)->getByteAmount();
        std::vector<uint8_t> subdata(begins, ends);
        values_.at(i)->interpretToValue(subdata);
    }
}

void ObdCommand::convertToSendableByteArray()
{
}

std::string ObdCommand::getRequestString(unsigned int desired_sid)
{
    std::stringstream ret;
    if(std::find(sids_.begin(), sids_.end(), desired_sid) != sids_.end()){
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
