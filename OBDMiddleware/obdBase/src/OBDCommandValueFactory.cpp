#include "OBDCommandValueFactory.h"

OBDCommandValueFactory* OBDCommandValueFactory::instance_;
OBDCommandValueFactory::~OBDCommandValueFactory()
{
}

AbstractOBDValue* OBDCommandValueFactory::createOBDValueFromInput(
        OBDCommandValueInput input, ValidityMappingMode mode, unsigned int autoPos)
{
    if(!input.is_mapping_){
        return new OBDCalculationValue(input, mode, autoPos);
    }else{
        switch(input.mapping_type_){
            case MappingType::BIT:
                return new OBDBitMappingValue(input, mode);
            case MappingType::VALUE:
                return new OBDValueMappingValue(input, mode, autoPos);
            case MappingType::BITCOMBINATION:
                return new OBDBitcombinationMappingValue(input, mode);
            default:
                break;
        }
    }
    return nullptr;
}

OBDCommandValueFactory* OBDCommandValueFactory::getInstance()
{
    if(instance_ == nullptr){
        instance_ = new OBDCommandValueFactory();
    }
    return instance_;
}

OBDCommandValueFactory::OBDCommandValueFactory()
{
}



