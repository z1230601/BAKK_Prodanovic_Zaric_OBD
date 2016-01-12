#ifndef OBDVALUEMAPPINGVALUE_H_
#define OBDVALUEMAPPINGVALUE_H_

#include "AbstractOBDValue.h"
#include "../../configurations/src/OBDCommandInputDefinitions.h"
#include <map>


class OBDValueMappingValue:public AbstractOBDValue
{
    public:
        OBDValueMappingValue();
        OBDValueMappingValue(OBDCommandValueInput input);
        OBDValueMappingValue(OBDCommandValueInput input, ValidityMappingMode mode, unsigned int auto_pos);
        OBDValueMappingValue(unsigned int byte_amount, std::string &name);
        OBDValueMappingValue(unsigned int byte_amount);
        virtual ~OBDValueMappingValue();

        std::string interpretToValue(std::vector<uint8_t> input);
        std::vector<uint8_t> interpretToByteArray(std::string value);

        std::map<unsigned int, std::string> getMapping();

        std::string getInterpretedValueAsString();
    private:
        std::map<unsigned int, std::string> mapping_;
        std::map<std::string, unsigned int> reverse_mapping_;

        void initMapping(OBDCommandValueInput input);
};

#endif /* OBDVALUEMAPPINGVALUE_H_ */
