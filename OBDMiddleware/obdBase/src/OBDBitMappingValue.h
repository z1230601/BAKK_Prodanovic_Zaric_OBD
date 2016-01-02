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
        virtual ~OBDBitMappingValue();

        std::string interpretToValue(std::vector<uint8_t> input);
        std::vector<uint8_t> interpretToByteArray(std::string value);

        std::map<unsigned int, std::string> getTrueMapping();
        std::map<unsigned int, std::string> getFalseMapping();

        void setBitScope(std::map<unsigned int, bool> bit_position_observed);
    private:
        std::map<unsigned int, std::string> true_mapping_;
        std::map<unsigned int, std::string> false_mapping_;

        std::map<std::string, unsigned int> reverse_true_mapping_;
        std::map<std::string, unsigned int> reverse_false_mapping_;

        std::map<unsigned int, bool> bit_position_observed_;
};

#endif /* OBDBITMAPPINGVALUE_H_ */
