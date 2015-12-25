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
#define COMMAND_TAG "command"

#include <vector>

typedef struct _ElmCommandInput_
{
        float version_;
        std::string basecommand_;
        std::string description_;
        std::string group_;
        std::string basevalueformat_;
        std::string subcommand_;
        std::string subvalueformat_;

        _ElmCommandInput_(float version, std::string basecommand,
                std::string description, std::string group,
                std::string basevalueformat, std::string subcommand,
                std::string subvalueformat)
        {
            version_ = version;
            basecommand_ = basecommand;
            description_ = description;
            group_ = group;
            basevalueformat_ = basevalueformat;
            subcommand_ = subcommand;
            subvalueformat_ = subvalueformat;
        }
        _ElmCommandInput_()
        {
            version_ = 0.0;
            basecommand_ = "";
            description_ = "";
            group_ = "";
            basevalueformat_ = "";
            subcommand_ = "";
            subvalueformat_ = "";
        }
} ElmCommandInput;

class ElmCommandXMLHandler : public DefaultXMLHandler
{
    private:
        std::vector<ElmCommandInput> parsed_commands_;
        ElmCommandInput current_elm_command_;

    public:
        void handleNode(xmlpp::Node* node);

        std::vector<ElmCommandInput> getParsedCommands();

};

#endif /* ELMCOMMANDXMLHANDLER_H_ */
