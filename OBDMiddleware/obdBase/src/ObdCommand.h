#ifndef OBDCOMMAND_H_
#define OBDCOMMAND_H_

#include "../../configurations/src/OBDCommandInputDefinitions.h"

#include <string>
#include <vector>
#include <map>

class AbstractOBDValue;

class ObdCommand
{
    public:
        ObdCommand();
        ObdCommand(std::vector<unsigned int> sids, unsigned int pid, std::string description, ValidityMappingMode mode);
        ObdCommand(std::vector<unsigned int> sids, OBDCommandInput input);
        virtual ~ObdCommand();

        //should not be void just for now till specified
        void interpretReceivedBytes(uint8_t data[]);
        void convertToSendableByteArray();
        void getRequestString();

        std::vector<unsigned int> getSids();
        unsigned int getPid();
        std::string getDescription();
        ValidityMappingMode getValidityMappingMode();
        std::map<unsigned int, bool> getValidityMapping();
        std::vector<AbstractOBDValue*> getValues();
    private:
        std::vector<unsigned int> sids_;
        unsigned int pid_;
        std::string description_;
        ValidityMappingMode mode_;
        std::map<unsigned int, bool> validity_mapping_;
        std::vector<AbstractOBDValue*> values_;
};

#endif /* OBDCOMMAND_H_ */
