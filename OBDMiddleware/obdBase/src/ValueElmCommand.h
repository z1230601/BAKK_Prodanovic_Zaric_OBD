#ifndef VALUEELMCOMMAND_H_
#define VALUEELMCOMMAND_H_

#include <vector>
#include <string>

typedef struct
{
        std::string command_;
        std::string value_;
        std::string value_format_;

} CommandType;

class ValueElmCommand
{
    private:
        CommandType base_command_;
        CommandType sub_command_;

        float min_req_version_;
        std::string description_;
        std::string group_;


        unsigned int getBitCountFromFormat(std::string valueFormat);
    public:
        ValueElmCommand();
        ValueElmCommand(float minReqElmVersion, std::string base_command,
                std::string description, std::string group,
                std::string base_value_format = "", std::string sub_command = "", std::string sub_value_format = "");
        virtual ~ValueElmCommand();

        std::string getValueAsString();
        bool valueStringCheckValid(std::string value);
        bool checkValueToFormat(std::string value);

        float getMinimumRequiredElmVersion();
        std::string getCommand();
        std::string getDescription();
        std::string getGroup();

        std::string getCompleteCommandAsString();

        void setMinimumRequiredElmVersion(float version);
        void setCommand(std::string command);
        void setDescription(std::string description);
        void setGroup(std::string group);
};

#endif /* VALUEELMCOMMAND_H_ */
