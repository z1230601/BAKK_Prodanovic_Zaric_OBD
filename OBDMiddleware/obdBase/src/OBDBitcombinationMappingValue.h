#ifndef OBDBITCOMBINATIONMAPPINGVALUE_H_
#define OBDBITCOMBINATIONMAPPINGVALUE_H_

#include "AbstractOBDValue.h"

class OBDBitcombinationMappingValue : public AbstractOBDValue
{
    public:
        OBDBitcombinationMappingValue();
        virtual ~OBDBitcombinationMappingValue();

        void interpretToValue(std::vector<uint8_t> input);
        void interpretToByteArray(double value);
};

#endif /* OBDBITCOMBINATIONMAPPINGVALUE_H_ */
