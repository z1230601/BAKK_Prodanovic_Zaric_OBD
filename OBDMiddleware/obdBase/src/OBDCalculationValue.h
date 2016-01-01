#ifndef OBDCALUCLATIONVALUE_H_
#define OBDCALUCLATIONVALUE_H_

#include <string>

#include "AbstractOBDValue.h"

class OBDCalculationValue : public AbstractOBDValue
{
    public:
        OBDCalculationValue();
        virtual ~OBDCalculationValue();

        void interpretToValue(uint8_t input[]);
        void interpretToByteArray(unsigned int value);

    private:
        double min_;
        double max_;
        std::string unit_;
};

#endif /* OBDCALUCLATIONVALUE_H_ */
