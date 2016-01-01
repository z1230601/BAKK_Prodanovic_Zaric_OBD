#ifndef ABSTRACTOBDCOMMANDVALUE_H_
#define ABSTRACTOBDCOMMANDVALUE_H_

#include <string>
#include <vector>

class AbstractOBDValue
{
    public:
        AbstractOBDValue();
        AbstractOBDValue(std::string &name, unsigned int interpreted_value, unsigned int byte_amount, std::vector<uint8_t> &uniterpreted);
        virtual ~AbstractOBDValue();

        virtual void interpretToValue(std::vector<uint8_t> input) = 0;
        virtual void interpretToByteArray(unsigned int value) = 0;

        std::string getName();
        unsigned int getInterpretedValue();
        unsigned int getByteAmount();
        std::vector<uint8_t> getUninterpretedValue();

    protected:
        std::string name_;
        unsigned int interpreted_value_;
        unsigned int byte_amount_;
        std::vector<uint8_t> uninterpreted_value_;
};

#endif /* ABSTRACTOBDCOMMANDVALUE_H_ */
