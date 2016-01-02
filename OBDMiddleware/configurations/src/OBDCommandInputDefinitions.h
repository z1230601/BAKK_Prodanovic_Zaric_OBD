#ifndef OBDCOMMANDINPUTDEFINITIONS_H_
#define OBDCOMMANDINPUTDEFINITIONS_H_

#include <string>
#include <map>
#include <vector>

#define SERVICEMODE_TAG "servicemode"
#define SERVICEID_TAG "sid"
#define OBDCOMMANDCOLLECTION_TAG "obdcommands"
#define OBDCOMMAND_TAG "obdcommand"
#define PARAMETERID_TAG "pid"
#define DESCRIPTION_TAG "description"
#define VALIDITYMAPPING_TAG "validitymapping"
#define VALUES_TAG "values"
#define VALUE_TAG "value"
#define NAME_TAG "name"
#define BYTES_TAG "bytes"
#define MIN_TAG "min"
#define MAX_TAG "max"
#define UNIT_TAG "unit"
#define MAPPING_TAG "mapping"
#define ENTRY_TAG "entry"
#define VALIDITYBIT_TAG "validitybit"

#define INTERPRETATION_ATTRIBUTE "interpretation"
#define TYPE_ATTRIBUTE "type"
#define SET_ATTRIBUTE "set"
#define FROM_ATTRIBUTE "from"
#define MODE_ATTRIBUTE "mode"

typedef enum
{
    OFF, AUTO, MANUAL
} ValidityMappingMode;

typedef enum
{
    NOTMAPPED, BIT, VALUE, BITCOMBINATION
} MappingType;

typedef struct
{
        std::string from_; //optional for mappingvalues
        std::string content_;
} ValidityBitEntry;

typedef struct _MappingEntry_
{
        std::string from_;
        std::string set_;
        std::string content_;
} MappingEntry;

typedef struct
{
        bool is_mapping_;
        uint8_t bytes_; // expected 1-4
        std::vector<ValidityBitEntry> man_validity_entries_;

        // calculation specific part
        std::string name_;
        double min_ = 0;
        double max_ = 0;
        std::string unit_;

        // mapping specific part
        MappingType mapping_type_;
        std::vector<MappingEntry> mapping_;
} OBDCommandValueInput;

typedef struct
{
        unsigned int pid_;
        std::string description_;
        ValidityMappingMode validity_mapping_mode_;
//        std::map<uint8_t, std::string> validity_mapping_;
        std::vector<OBDCommandValueInput> values_;
} OBDCommandInput;

typedef struct
{
        std::vector<unsigned int> sid_;
        std::vector<OBDCommandInput> commands_;
} ServiceModeInput;
#endif /* OBDCOMMANDINPUTDEFINITIONS_H_ */
