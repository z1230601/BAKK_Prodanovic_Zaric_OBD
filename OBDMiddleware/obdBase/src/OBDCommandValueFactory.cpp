#include "OBDCommandValueFactory.h"

OBDCommandValueFactory* OBDCommandValueFactory::instance_;
OBDCommandValueFactory::~OBDCommandValueFactory()
{
}

AbstractOBDValue* OBDCommandValueFactory::createOBDValueFromInput(
        OBDCommandValueInput input)
{
    if(!input.is_mapping_){
        return new OBDCalculationValue(input);
    }else{
        switch(input.mapping_type_){
            case MappingType::BIT:
                return new OBDBitMappingValue(input);
            case MappingType::VALUE:
                return new OBDValueMappingValue(input);
            case MappingType::BITCOMBINATION:
                return new OBDBitcombinationMappingValue(input);
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



