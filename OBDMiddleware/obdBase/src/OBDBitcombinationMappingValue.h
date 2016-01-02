#ifndef OBDBITCOMBINATIONMAPPINGVALUE_H_
#define OBDBITCOMBINATIONMAPPINGVALUE_H_

#include "AbstractOBDValue.h"

class OBDBitcombinationMappingValue : public AbstractOBDValue
{
    public:
        OBDBitcombinationMappingValue();
        virtual ~OBDBitcombinationMappingValue();

        std::string interpretToValue(std::vector<uint8_t> input);
        std::vector<uint8_t> interpretToByteArray(std::string value);
};

#endif /* OBDBITCOMBINATIONMAPPINGVALUE_H_ */
