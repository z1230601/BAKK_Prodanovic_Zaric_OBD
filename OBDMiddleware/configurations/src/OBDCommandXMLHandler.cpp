#include "OBDCommandXMLHandler.h"
#include "libxml++/libxml++.h"

#include <string>
#include <algorithm>
#include <stdexcept>

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
        parsePidTag(node, command);
    }

    if(node->get_name().compare(DESCRIPTION_TAG) == 0)
    {
        command.description_ = getTextFromNode(node);
    }

    if(node->get_name().compare(VALIDITYMAPPING_TAG) == 0)
    {
        parseValidityMappingTag(node, command);
    }

    if(node->get_name().compare(VALUE_TAG) == 0)
    {
        parseValueTag(node, command);
    }
}

void OBDCommandXMLHandler::handleValueInput(xmlpp::Node* node)
{
    if(parsed_data_.empty() || parsed_data_.back().commands_.empty()
            || parsed_data_.back().commands_.back().values_.empty())
    {
        return;
    }

    OBDCommandValueInput value = parsed_data_.back().commands_.back().values_
            .back();

    if(node->get_name().compare(NAME_TAG))
    {
        value.name_ = getTextFromNode(node);
    }

    if(node->get_name().compare(BYTES_TAG))
    {
        try
        {
            value.bytes_ = std::stoi(getTextFromNode(node));
        } catch (std::exception &e)
        {
            //TODO:ERRORHANDLING
        }
    }

    if(node->get_name().compare(MIN_TAG))
    {
        try
        {
            value.min_ = std::stoi(getTextFromNode(node));
        } catch (std::exception &e)
        {
            //TODO: ERRORHANDLING
        }
    }

    if(node->get_name().compare(MAX_TAG))
    {
        try
        {
            value.max_ = std::stoi(getTextFromNode(node));
        } catch (std::exception &e)
        {
            //TODO: ERRORHANDLING
        }
    }

    if(node->get_name().compare(UNIT_TAG))
    {
        value.unit_ = getTextFromNode(node);
    }

    if(node->get_name().compare(MAPPING_TAG))
    {
        parseMappingTag(node, value);
    }

    if(node->get_name().compare(ENTRY_TAG))
    {
        parseEntryTag(node, value);
    }

    if(node->get_name().compare(VALIDITYBIT_TAG))
    {
        parseValidityBitTag(node, value);
    }

}

void OBDCommandXMLHandler::parseValueTag(xmlpp::Node* node,
        OBDCommandInput &command)
{
    xmlpp::Element* element = dynamic_cast<xmlpp::Element*>(node);

    if(element == nullptr)
    {
        return;
    }

    std::map<std::string, std::string> attributes = getAttributesFromElement(
            element);
    if(attributes.find(INTERPRETATION_ATTRIBUTE) != attributes.end())
    {
        command.values_.push_back(OBDCommandValueInput { });
        command.values_.back().is_mapping_ =
                attributes[INTERPRETATION_ATTRIBUTE].compare("Mapping") == 0;
    } else
    {
        //TODO: ERROR HANDLING DO SOMETHING
    }
}

void OBDCommandXMLHandler::parseValidityMappingTag(xmlpp::Node* node,
        OBDCommandInput &command)
{
    xmlpp::Element* element = dynamic_cast<xmlpp::Element*>(node);

    if(element == nullptr)
    {
        return;
    }
    std::string content = getTextFromNode(node);
    std::map<std::string, std::string> attributes = getAttributesFromElement(
            element);

    if(!content.empty() && content.compare("true") == 0)
    {
        if(attributes.find(MODE_ATTRIBUTE) != attributes.end())
        {
            if(attributes[MODE_ATTRIBUTE].compare("manual"))
            {
                command.validity_mapping_mode_ = ValidityMappingMode::MANUAL;
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

void OBDCommandXMLHandler::parsePidTag(xmlpp::Node* node,
        OBDCommandInput &command)
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

void OBDCommandXMLHandler::parseMappingTag(xmlpp::Node* node,
        OBDCommandValueInput &value)
{
    xmlpp::Element* element = dynamic_cast<xmlpp::Element*>(node);

    if(element == nullptr)
    {
        return;
    }
    std::map<std::string, std::string> attributes = getAttributesFromElement(
            element);

    if(attributes.find(TYPE_ATTRIBUTE) != attributes.end())
    {
        if(attributes[TYPE_ATTRIBUTE].compare("bit"))
        {
            value.mapping_type_ = MappingType::BIT;
        } else if(attributes[TYPE_ATTRIBUTE].compare("bitcombination"))
        {
            value.mapping_type_ = MappingType::BITCOMBINATION;
        } else if(attributes[TYPE_ATTRIBUTE].compare("value"))
        {
            value.mapping_type_ = MappingType::VALUE;
        } else
        {
            throw std::runtime_error(
                    "Wrong format of Mapping type: "
                            + attributes[TYPE_ATTRIBUTE]
                            + "\nexpected: bit||bitcombination||value");
        }
    } else
    {
        throw std::runtime_error("No mapping mode!");
    }

}

void OBDCommandXMLHandler::parseEntryTag(xmlpp::Node* node,
        OBDCommandValueInput &value)
{
    xmlpp::Element* element = dynamic_cast<xmlpp::Element*>(node);

    if(element == nullptr)
    {
        return;
    }
    std::string content = getTextFromNode(node);
    std::map<std::string, std::string> attributes = getAttributesFromElement(
            element);

    MappingEntry entry;
    if(attributes.find(SET_ATTRIBUTE) != attributes.end())
    {
        entry.set_ = attributes[SET_ATTRIBUTE];
    }
    if(attributes.find(FROM_ATTRIBUTE) != attributes.end())
    {
        entry.from_ = attributes[FROM_ATTRIBUTE];
    }
    entry.content_ = content;
    value.mapping_.push_back(entry);
}

void OBDCommandXMLHandler::parseValidityBitTag(xmlpp::Node* node,
        OBDCommandValueInput &value)
{
    xmlpp::Element* element = dynamic_cast<xmlpp::Element*>(node);

    if(element == nullptr)
    {
        return;
    }
    std::string content = getTextFromNode(node);
    std::map<std::string, std::string> attributes = getAttributesFromElement(
            element);
    ValidityBitEntry entry;
    if(attributes.find(FROM_ATTRIBUTE) != attributes.end())
    {
        entry.from_ = attributes[FROM_ATTRIBUTE];
    }
    entry.content_ = content;
    value.man_validity_entries_.push_back(entry);
}

std::vector<ServiceModeInput> OBDCommandXMLHandler::getParsedData() {
    return parsed_data_;
}
