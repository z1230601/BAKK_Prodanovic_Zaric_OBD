#include "ElmCommandXMLHandler.h"

void ElmCommandXMLHandler::handleNode(xmlpp::Node* node)
{
    if(node->get_name().compare(VERSION_TAG) == 0)
    {
        min_req_version_ = std::stof(getTextFromNode(node));
    }
    if(node->get_name().compare(BASECOMMMAND_TAG) == 0)
    {
        base_command_.command_ = getTextFromNode(node);
    }
    if(node->get_name().compare(DESCRIPTION_TAG) == 0)
    {
        description_ = getTextFromNode(node);
    }
    if(node->get_name().compare(GROUP_TAG) == 0)
    {
        group_ = getTextFromNode(node);
    }
    if(node->get_name().compare(BASEVALUEFORMAT_TAG) == 0)
    {
        base_command_.value_format_ = getTextFromNode(node);
    }
    if(node->get_name().compare(SUBCOMMAND_TAG) == 0)
    {
        sub_command_.command_ = getTextFromNode(node);
    }
    if(node->get_name().compare(SUBVALUEFORMAT_TAG) == 0)
    {
        sub_command_.value_format_ = getTextFromNode(node);
    }
}

float ElmCommandXMLHandler::getMinimumRequiredElmVersion()
{
    return min_req_version_;
}

std::string ElmCommandXMLHandler::getBaseCommand() {
    return base_command_.command_;
}

std::string ElmCommandXMLHandler::getDescription()
{
    return description_;
}

std::string ElmCommandXMLHandler::getGroup()
{
    return group_;
}

std::string ElmCommandXMLHandler::getBaseValueFormat() {
    return base_command_.value_format_;
}

std::string ElmCommandXMLHandler::getSubCommand() {
    return sub_command_.command_;
}

std::string ElmCommandXMLHandler::getSubValueFormat() {
    return sub_command_.value_format_;
}
