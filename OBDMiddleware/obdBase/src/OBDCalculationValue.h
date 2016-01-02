#ifndef OBDCALCULATIONVALUE_H_
#define OBDCALCULATIONVALUE_H_

#include <string>

#include "AbstractOBDValue.h"
#include "../../configurations/src/OBDCommandInputDefinitions.h"

class OBDCalculationValue : public AbstractOBDValue
{
    public:
        OBDCalculationValue();
        OBDCalculationValue(std::string &name, unsigned int byte_amount, double min, double max, std::string &unit);
        OBDCalculationValue(OBDCommandValueInput input);
        virtual ~OBDCalculationValue();

        void interpretCalculationValue(std::vector<uint8_t> input);
        void interpretCalculationByteArray(double value);

        std::string interpretToValue(std::vector<uint8_t> input);
        std::vector<uint8_t> interpretToByteArray(std::string value);

        double getMin();
        double getMax();
        std::string getUnit();

    private:
        double min_;
        double max_;
        std::string unit_;
};

#endif /* OBDCALCULATIONVALUE_H_ */
