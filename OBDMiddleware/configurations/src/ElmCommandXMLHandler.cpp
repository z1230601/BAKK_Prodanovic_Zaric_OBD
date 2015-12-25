#include "ElmCommandXMLHandler.h"

void ElmCommandXMLHandler::handleNode(xmlpp::Node* node)
{
    if(node->get_name().compare(VERSION_TAG) == 0)
    {
        current_elm_command_.version_ = std::stof(getTextFromNode(node));
    }
    if(node->get_name().compare(BASECOMMMAND_TAG) == 0)
    {
        current_elm_command_.basecommand_ = getTextFromNode(node);
    }
    if(node->get_name().compare(DESCRIPTION_TAG) == 0)
    {
        current_elm_command_.description_ = getTextFromNode(node);
    }
    if(node->get_name().compare(GROUP_TAG) == 0)
    {
        current_elm_command_.group_ = getTextFromNode(node);
    }
    if(node->get_name().compare(BASEVALUEFORMAT_TAG) == 0)
    {
        current_elm_command_.basevalueformat_ = getTextFromNode(node);
    }
    if(node->get_name().compare(SUBCOMMAND_TAG) == 0)
    {
        current_elm_command_.subcommand_ = getTextFromNode(node);
    }
    if(node->get_name().compare(SUBVALUEFORMAT_TAG) == 0)
    {
        current_elm_command_.subvalueformat_ = getTextFromNode(node);
    }
    if(node->get_name().compare(COMMAND_TAG) == 0)
    {
        if(current_elm_command_.version_ == 0.0) return;

        parsed_commands_.push_back(current_elm_command_);
        current_elm_command_ = ElmCommandInput();
    }
}

std::vector<ElmCommandInput> ElmCommandXMLHandler::getParsedCommands() {
    if(current_elm_command_.version_ != 0.0){
        parsed_commands_.push_back(current_elm_command_);
        current_elm_command_ = ElmCommandInput();
    }
    return parsed_commands_;
}
