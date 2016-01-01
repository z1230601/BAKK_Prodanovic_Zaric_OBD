#ifndef OBDVALUEMAPPINGVALUE_H_
#define OBDVALUEMAPPINGVALUE_H_

#include "AbstractOBDValue.h"
#include <map>
#include <string>


class OBDValueMappingValue:public AbstractOBDValue
{
    public:
        OBDValueMappingValue();
        virtual ~OBDValueMappingValue();

        void interpretToValue(std::vector<uint8_t> input);
        void interpretToByteArray(double value);
        std::string getInterpretedValueAsString();
    private:
        std::map<uint8_t, std::string> mapping_;
};

#endif /* OBDVALUEMAPPINGVALUE_H_ */
