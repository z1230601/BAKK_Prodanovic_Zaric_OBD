#ifndef OBDCOMMANDXMLHANDLER_H_
#define OBDCOMMANDXMLHANDLER_H_

#include "DefaultXMLHandler.h"s

#define SERVICEMODE_TAG "servicemode"
#define SERVICEID_TAG "sid"
#define OBDCOMMANDCOLLECTION_TAG "obdcommands"
#define OBDCOMMAND_TAG "obdcommand"
#define PARAMETERID_TAG "pid"
#define DESCRIPTION_TAG "description"
#define VALIDITYMAPPING_TAG "validitymapping"
#define VALUE_TAG "value"
#define NAME_TAG "name"
#define BYTES_TAG "bytes"
#define MIN_TAG "min"
#define MAX_TAG "max"
#define UNIT_TAG "unit"
#define MAPPING_TAG "mapping"
#define ENTRY_TAG "entry"
#define VALIDITYBIT_TAG "validitybit"

#define INTERPRETATION_ATTRIBTUE "interpretation"
#define TYPE_ATTRIBTUE "type"
#define SET_ATTRIBTUE "set"
#define FROM_ATTRIBUTE "from"
#define MODE_ATTRIBTUE "mode"

typedef enum {
    AUTO,
    MANUAL
}ValidityMappingMode;

typedef struct{
        std::string name_;
        uint8_t bytes; // expected 1-4
        int min_;
        int max_;
}OBDCommandValueInput;

typedef struct {
        unsigned int pid_;
        std::string description_;
        ValidityMappingMode validitymapping_;
        std::vector<OBDCommandValueInput> values_;
}OBDCommand;


typedef struct {
        unsigned int sid_;
        std::vector<OBDCommand> commands_;
}ServiceModeInput;

class OBDCommandXMLHandler : public DefaultXMLHandler
{
    private:
        std::vector<unsigned int> sids_;
        std::vector<>
    public:
        OBDCommandXMLHandler();
        virtual ~OBDCommandXMLHandler();

        void handleNode(xmlpp::Node* node);
};

#endif /* OBDCOMMANDXMLHANDLER_H_ */
