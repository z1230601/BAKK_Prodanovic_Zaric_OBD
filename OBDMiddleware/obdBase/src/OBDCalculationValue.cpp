#include "OBDCalculationValue.h"
#include <math.h>
#include <sstream>
#include <boost/lexical_cast.hpp>

OBDCalculationValue::OBDCalculationValue()
        : AbstractOBDValue()
{
}

OBDCalculationValue::OBDCalculationValue(std::string &name,
        unsigned int byte_amount, double min, double max, std::string &unit)
        : AbstractOBDValue(name, byte_amount), min_(min), max_(max), unit_(unit)
{
}
OBDCalculationValue::OBDCalculationValue(OBDCommandValueInput input)
        : AbstractOBDValue(input.name_, input.bytes_), min_(input.min_), max_(
                input.max_), unit_(input.unit_)
{

}

OBDCalculationValue::~OBDCalculationValue()
{
}

void OBDCalculationValue::interpretToValue(std::vector<uint8_t> input)
{
    unsigned int compound_value = calculateCompoundValue(input);

    double scale = (max_ - min_) / (pow(2.0, byte_amount_ * 8.0) - 1);

    interpreted_value_ = compound_value * scale + min_;

    uninterpreted_value_ = compound_value;
}

void OBDCalculationValue::interpretToByteArray(double value)
{
    interpreted_value_ = value;
    interpreted_value_ = std::min(interpreted_value_, max_);
    interpreted_value_ = std::max(interpreted_value_, min_);

    double scale = (max_ - min_) / (pow(2.0, byte_amount_ * 8.0) - 1);

    uninterpreted_value_ = (interpreted_value_ - min_) / scale;
}

double OBDCalculationValue::getMin()
{
    return min_;
}

double OBDCalculationValue::getMax()
{
    return max_;
}

std::string OBDCalculationValue::getInterpretedValueAsString()
{
    return boost::lexical_cast<std::string>(interpreted_value_);
}

std::string OBDCalculationValue::getUnit()
{
    return unit_;
}
