#include "ObdCommand.h"
#include "OBDCommandValueFactory.h"

ObdCommand::ObdCommand()
        : pid_(0), description_(""), mode_(ValidityMappingMode::OFF)
{
}

ObdCommand::ObdCommand(std::vector<unsigned int> sids, unsigned int pid,
        std::string description, ValidityMappingMode mode)
        : sids_(sids), pid_(pid), description_(description), mode_(mode)
{
    //TODO: depending on  mode init mapping
}

ObdCommand::ObdCommand(std::vector<unsigned int> sids, OBDCommandInput input)
        : sids_(sids), pid_(input.pid_), description_(input.description_), mode_(input.validity_mapping_mode_)
{
    for(unsigned int i = 0; i < input.values_.size(); i++){ //OBDCommandValueInput value : input.values_){
        values_.push_back(OBDCommandValueFactory::getInstance()->createOBDValueFromInput(input.values_.at(i), input.validity_mapping_mode_, i));
    }
}

ObdCommand::~ObdCommand()
{
}

void ObdCommand::interpretReceivedBytes(uint8_t data[])
{
}

void ObdCommand::convertToSendableByteArray()
{
}

void ObdCommand::getRequestString()
{
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

ValidityMappingMode ObdCommand::getValidityMappingMode()
{
    return mode_;
}

std::map<unsigned int, bool> ObdCommand::getValidityMapping()
{
    return validity_mapping_;
}

std::vector<AbstractOBDValue*> ObdCommand::getValues()
{
    return values_;
}
