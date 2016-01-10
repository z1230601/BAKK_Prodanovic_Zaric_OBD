#ifndef OBDBITCOMBINATIONMAPPINGVALUE_H_
#define OBDBITCOMBINATIONMAPPINGVALUE_H_

#include "../../configurations/src/OBDCommandInputDefinitions.h"
#include "AbstractOBDValue.h"
#include <map>

class OBDBitcombinationMappingValue : public AbstractOBDValue
{
    public:
        OBDBitcombinationMappingValue();
        OBDBitcombinationMappingValue(unsigned int byte_amount);
        OBDBitcombinationMappingValue(OBDCommandValueInput input);
        OBDBitcombinationMappingValue(OBDCommandValueInput input,
                ValidityMappingMode mode);
        virtual ~OBDBitcombinationMappingValue();

        std::string interpretToValue(std::vector<uint8_t> input);
        std::vector<uint8_t> interpretToByteArray(std::string value);

        std::map<unsigned int, std::map<unsigned int, std::string> > getMapping();
        unsigned int getKeyFromBitPositionString(std::string value);

        void setBitcombinationScope(std::map<unsigned int, bool> valid_scope);
        std::map<unsigned int, bool> getBitcombinationScope();

        void setValidityByte(uint8_t byte);
        bool isValueValid();

        std::string getInterpretedValueAsString();

    private:
        std::map<unsigned int, std::map<unsigned int, std::string> > mapping_;
        std::map<unsigned int, std::map<std::string, unsigned int> > reverse_mapping_;

        std::map<unsigned int, bool> bitcombination_observed_;
        std::map<unsigned int, uint8_t> validity_mask_mapping_;

        unsigned int countOccurencesOfZero(unsigned int value);
};

#endif /* OBDBITCOMBINATIONMAPPINGVALUE_H_ */
