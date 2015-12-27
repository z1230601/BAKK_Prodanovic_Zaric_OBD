#ifndef OBDCOMMANDXMLHANDLER_H_
#define OBDCOMMANDXMLHANDLER_H_

#include "DefaultXMLHandler.h"
#include "OBDCommandInputDefinitions.h"

#include <string>
#include <vector>
#include <map>


class OBDCommandXMLHandler : public DefaultXMLHandler
{
    private:
        std::vector<ServiceModeInput> parsed_data_;
        std::vector<std::string> command_tags_;
        std::vector<std::string> value_tags_;
        std::vector<std::string> service_tags_;


        void parseValueTag(xmlpp::Node* node, OBDCommandInput &command);
        void parseValidityMappingTag(xmlpp::Node* node, OBDCommandInput &command);
        void parsePidTag(xmlpp::Node* node, OBDCommandInput &command);
        void parseMappingTag(xmlpp::Node* node, OBDCommandValueInput &value);
        void parseEntryTag(xmlpp::Node* node, OBDCommandValueInput &value);
        void parseValidityBitTag(xmlpp::Node* node, OBDCommandValueInput &value);

    public:
        OBDCommandXMLHandler();
        virtual ~OBDCommandXMLHandler();

        void handleNode(xmlpp::Node* node);
        void handleServiceInput(xmlpp::Node* node);
        void handleCommandInput(xmlpp::Node* node);
        void handleValueInput(xmlpp::Node* node);
};

#endif /* OBDCOMMANDXMLHANDLER_H_ */
