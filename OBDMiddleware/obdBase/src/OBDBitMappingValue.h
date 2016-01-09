#ifndef OBDBITMAPPINGVALUE_H_
#define OBDBITMAPPINGVALUE_H_

#include "AbstractOBDValue.h"
#include "../../configurations/src/OBDCommandInputDefinitions.h"
#include <map>

class OBDBitMappingValue : public AbstractOBDValue
{
    public:
        OBDBitMappingValue();
        OBDBitMappingValue(unsigned int byte_amount);
        OBDBitMappingValue(OBDCommandValueInput input);
        OBDBitMappingValue(OBDCommandValueInput input, ValidityMappingMode mode);
        virtual ~OBDBitMappingValue();

        std::string interpretToValue(std::vector<uint8_t> input);
        std::vector<uint8_t> interpretToByteArray(std::string value);

        std::map<unsigned int, std::string> getTrueMapping();
        std::map<unsigned int, std::string> getFalseMapping();

        void setBitScope(std::map<unsigned int, bool> bit_position_observed);
        std::map<unsigned int, bool> getBitScope();

        void setValidityByte(uint8_t byte);
        bool isValueValid();

    private:
        std::map<unsigned int, std::string> true_mapping_;
        std::map<unsigned int, std::string> false_mapping_;

        std::map<std::string, unsigned int> reverse_true_mapping_;
        std::map<std::string, unsigned int> reverse_false_mapping_;

        std::map<unsigned int, bool> bit_position_observed_;

        void initMapping(OBDCommandValueInput input);
        void initManualValidityMapping(OBDCommandValueInput input);
        void initAutomaticValidityMapping();
};

#endif /* OBDBITMAPPINGVALUE_H_ */
