#ifndef OBDCOMMAND_H_
#define OBDCOMMAND_H_

#include "../../configurations/src/OBDCommandInputDefinitions.h"
#include "OBDBitcombinationMappingValue.h"

#include <string>
#include <vector>
#include <map>

class AbstractOBDValue;

class ObdCommand
{
    public:
        ObdCommand();
        ObdCommand(std::vector<unsigned int> sids, unsigned int pid,
                std::string description);
        ObdCommand(std::vector<unsigned int> sids, OBDCommandInput input);
        virtual ~ObdCommand();

        //should not be void just for now till specified
        void interpretReceivedBytes(std::vector<uint8_t> data);
        std::vector<uint8_t> convertToSendableByteArray();
        std::string getRequestString(unsigned int desired_sid);

        std::vector<unsigned int> getSids();
        unsigned int getPid();
        std::string getDescription();
        std::vector<AbstractOBDValue*> getValues();

        OBDBitcombinationMappingValue* getFirstValueOfTypeBitcombination();
    private:
        std::vector<unsigned int> sids_;
        unsigned int pid_;
        std::string description_;
        std::vector<AbstractOBDValue*> values_;

        bool is_validity_mapping_active_;
};

#endif /* OBDCOMMAND_H_ */
