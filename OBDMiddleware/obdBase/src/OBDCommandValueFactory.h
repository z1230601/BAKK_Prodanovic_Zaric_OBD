#ifndef OBDCOMMANDVALUEFACTORY_H_
#define OBDCOMMANDVALUEFACTORY_H_

#include "OBDBitMappingValue.h"
#include "OBDCalculationValue.h"
#include "OBDBitcombinationMappingValue.h"
#include "OBDValueMappingValue.h"
#include "../../configurations/src/OBDCommandInputDefinitions.h"

class OBDCommandValueFactory
{

        OBDCommandValueFactory(OBDCommandValueFactory&) = delete;
        OBDCommandValueFactory(OBDCommandValueFactory&&) = delete;

    public:
        virtual ~OBDCommandValueFactory();
        AbstractOBDValue* createOBDValueFromInput(OBDCommandValueInput input);
        static OBDCommandValueFactory* getInstance();

    private:
        OBDCommandValueFactory();
        static OBDCommandValueFactory* instance_;

};

#endif /* OBDCOMMANDVALUEFACTORY_H_ */
