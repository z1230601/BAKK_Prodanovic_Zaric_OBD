#ifndef ABSTRACTOBDCOMMANDVALUE_H_
#define ABSTRACTOBDCOMMANDVALUE_H_

#include <string>
#include <vector>

class AbstractOBDValue
{
    public:
        AbstractOBDValue();
        AbstractOBDValue(std::string &name, double interpreted_value, unsigned int byte_amount, unsigned int uninterpreted);
        AbstractOBDValue(std::string &name, unsigned int byte_amount);
        AbstractOBDValue(unsigned int byte_amount);
        virtual ~AbstractOBDValue();

        virtual std::string interpretToValue(std::vector<uint8_t> input) = 0;
        virtual std::vector<uint8_t> interpretToByteArray(std::string value) = 0;

        std::string getName();
        double getInterpretedValue();
        unsigned int getByteAmount();
        unsigned int getUninterpretedValue();
        unsigned int calculateCompoundValue(std::vector<uint8_t> input);
        std::vector<uint8_t> calculateByteArrayFromCompoundValue(unsigned int input);

    protected:
        std::string name_;
        double interpreted_value_;
        unsigned int byte_amount_;
        unsigned int uninterpreted_value_;
};

#endif /* ABSTRACTOBDCOMMANDVALUE_H_ */
