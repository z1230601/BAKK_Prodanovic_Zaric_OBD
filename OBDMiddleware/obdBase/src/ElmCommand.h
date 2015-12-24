#ifndef ELMCOMMAND_H_
#define ELMCOMMAND_H_

#include <vector>
#include <string>

typedef struct
{
        std::string command_;
        std::string value_;
        std::string value_format_;

} CommandType;

class ElmCommand
{
    private:
        float min_req_version_;

        CommandType base_command_;
        CommandType sub_command_;

        std::string description_;
        std::string group_;

        unsigned int getBitCountFromFormat(std::string valueFormat);
        bool checkFormatValue(std::string &value, std::string &format);
    public:
        ElmCommand();
        ElmCommand(float minReqElmVersion, std::string base_command,
                std::string description, std::string group,
                std::string base_value_format = "", std::string sub_command = "", std::string sub_value_format = "");
        virtual ~ElmCommand();

        bool isValidValue(std::string value);
        bool checkBaseValueToFormat(std::string value);
        bool checkSubValueToFormat(std::string value);

        float getMinimumRequiredElmVersion();
        std::string getDescription();
        std::string getGroup();

        std::string getCompleteCommandAsString();

        void setBaseValue(std::string value);
        void setSubValue(std::string subvalue);

};

#endif /* ELMCOMMAND_H_ */
