#ifndef OBDVALUEMAPPINGVALUE_H_
#define OBDVALUEMAPPINGVALUE_H_

#include "AbstractOBDValue.h"

class OBDValueMappingValue:public AbstractOBDValue
{
    public:
        OBDValueMappingValue();
        virtual ~OBDValueMappingValue();

        void interpretToValue(std::vector<uint8_t> input);
        void interpretToByteArray(double value);



};

#endif /* OBDVALUEMAPPINGVALUE_H_ */
