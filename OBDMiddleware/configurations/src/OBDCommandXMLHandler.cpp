#include "OBDCommandXMLHandler.h"
#include "libxml++/libxml++.h"

#include <string>
#include <algorithm>

OBDCommandXMLHandler::OBDCommandXMLHandler()
{
    service_tags_.push_back(SERVICEMODE_TAG);
    service_tags_.push_back(SERVICEID_TAG);
    service_tags_.push_back(OBDCOMMAND_TAG);

    command_tags_.push_back(PARAMETERID_TAG);
    command_tags_.push_back(DESCRIPTION_TAG);
    command_tags_.push_back(VALIDITYMAPPING_TAG);
    command_tags_.push_back(VALUE_TAG);

    value_tags_.push_back(NAME_TAG);
    value_tags_.push_back(BYTES_TAG);
    value_tags_.push_back(MIN_TAG);
    value_tags_.push_back(MAX_TAG);
    value_tags_.push_back(UNIT_TAG);
    value_tags_.push_back(MAPPING_TAG);
    value_tags_.push_back(ENTRY_TAG);
    value_tags_.push_back(VALIDITYBIT_TAG);

}

OBDCommandXMLHandler::~OBDCommandXMLHandler()
{

}

void OBDCommandXMLHandler::handleNode(xmlpp::Node* node)
{
    if(std::find(service_tags_.begin(), service_tags_.end(), node->get_name())
            != service_tags_.end())
    {
        handleServiceInput(node);
    }

    if(std::find(command_tags_.begin(), command_tags_.end(), node->get_name())
            != command_tags_.end())
    {
        handleCommandInput(node);
    }

    if(std::find(value_tags_.begin(), value_tags_.end(), node->get_name())
            != value_tags_.end())
    {
        handleValueInput(node);
    }

}

void OBDCommandXMLHandler::handleServiceInput(xmlpp::Node* node)
{
    if(node->get_name().compare(SERVICEMODE_TAG) == 0)
    {
        parsed_data_.push_back(ServiceModeInput { });
    }

    if(node->get_name().compare(SERVICEID_TAG) == 0)
    {
        try
        {
            parsed_data_.back().sid_.push_back(
                    (unsigned int) std::stoi(getTextFromNode(node)));
        } catch (std::exception &e)
        {
            //TODO: do something
        }
    }

    if(node->get_name().compare(OBDCOMMAND_TAG) == 0)
    {
        parsed_data_.back().commands_.push_back(OBDCommandInput { });
    }
}

void OBDCommandXMLHandler::handleCommandInput(xmlpp::Node* node)
{
    if(parsed_data_.empty() || parsed_data_.back().commands_.empty())
    {
        return;
    }

    OBDCommandInput command = parsed_data_.back().commands_.back();
    if(node->get_name().compare(PARAMETERID_TAG) == 0)
    {
        try
        {
            //convert pid string in hex format to int with stoi base 16
            command.pid_ = std::stoi(getTextFromNode(node), nullptr, 16);
        } catch (std::exception &e)
        {
            //TODO: do something
        }
    }
    if(node->get_name().compare(DESCRIPTION_TAG) == 0)
    {
        command.description_ = getTextFromNode(node);
    }

    if(node->get_name().compare(VALIDITYMAPPING_TAG) == 0)
    {
        xmlpp::Element* element = dynamic_cast<xmlpp::Element*>(node);

        if(element == nullptr)
        {
            return;
        }
        std::string content = getTextFromNode(node);
        std::map<std::string, std::string> attributes =
                getAttributesFromElement(element);

        if(!content.empty() && content.compare("true") == 0)
        {
            if(attributes.find(MODE_ATTRIBUTE) != attributes.end())
            {
                if(attributes[MODE_ATTRIBUTE].compare("manual"))
                {
                    command.validity_mapping_mode_ =
                            ValidityMappingMode::MANUAL;
                } else
                {
                    command.validity_mapping_mode_ = ValidityMappingMode::AUTO;
                }
            } else
            {
                command.validity_mapping_mode_ = ValidityMappingMode::AUTO;
            }
        } else
        {
            command.validity_mapping_mode_ = ValidityMappingMode::OFF;
        }
    }

    if(node->get_name().compare(VALUE_TAG) == 0)
    {
        xmlpp::Element* element = dynamic_cast<xmlpp::Element*>(node);

        if(element == nullptr)
        {
            return;
        }

        std::map<std::string, std::string> attributes =
                getAttributesFromElement(element);
        if(attributes.find(INTERPRETATION_ATTRIBUTE) != attributes.end())
        {
            command.values_.push_back(OBDCommandValueInput { });
            command.values_.back().is_mapping_ =
                    attributes[INTERPRETATION_ATTRIBUTE].compare("Mapping")
                            == 0;
        } else
        {
            //TODO: ERROR HANDLING DO SOMETHING
        }
    }
}
void OBDCommandXMLHandler::handleValueInput(xmlpp::Node* node)
{
    if(parsed_data_.empty() || parsed_data_.back().commands_.empty()
            || parsed_data_.back().commands_.back().values_.empty())
    {
        return;
    }

    OBDCommandValueInput command = parsed_data_.back().commands_.back().values_
            .back();

}
