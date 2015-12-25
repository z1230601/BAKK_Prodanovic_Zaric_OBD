#ifndef ELMCOMMANDXMLHANDLER_H_
#define ELMCOMMANDXMLHANDLER_H_

#include "DefaultXMLHandler.h"
#include <string>

#define VERSION_TAG "version"
#define BASECOMMMAND_TAG "basecommand"
#define DESCRIPTION_TAG "description"
#define GROUP_TAG "group"
#define BASEVALUEFORMAT_TAG "basevalueformat"
#define SUBCOMMAND_TAG "subcommand"
#define SUBVALUEFORMAT_TAG "subvalueformat"

typedef struct
{
        std::string command_;
        std::string value_format_;

} CommandType;

class ElmCommandXMLHandler : public DefaultXMLHandler
{
    private:
        float min_req_version_;

        CommandType base_command_;
        CommandType sub_command_;

        std::string description_;
        std::string group_;

    public:
        void handleNode(xmlpp::Node* node);

        float getMinimumRequiredElmVersion();

        std::string getBaseCommand();
        std::string getDescription();
        std::string getGroup();
        std::string getBaseValueFormat();
        std::string getSubCommand();
        std::string getSubValueFormat();

};

#endif /* ELMCOMMANDXMLHANDLER_H_ */
