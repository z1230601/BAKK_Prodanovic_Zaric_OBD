#include "DefaultXMLHandler.h"

DefaultXMLHandler::DefaultXMLHandler()
{
}

DefaultXMLHandler::~DefaultXMLHandler()
{
}

std::string DefaultXMLHandler::getTextFromNode(xmlpp::Node* node)
{
    xmlpp::Element* node_as_element = dynamic_cast<xmlpp::Element*>(node);
    if(node_as_element == NULL) {
        return "";
    }

    xmlpp::TextNode* text = node_as_element->get_child_text();
    if(text == NULL)
    {
        return "";
    }
    return std::string(text->get_content().c_str());
}

std::map<std::string, std::string> DefaultXMLHandler::getAttributesFromElement(
        xmlpp::Element* el)
{
    std::map<std::string, std::string> ret;
    std::list<xmlpp::Attribute*> list = el->get_attributes();
    for(xmlpp::Attribute* attr : list)
    {
        ret[std::string(attr->get_name().c_str())] = std::string(
                attr->get_value().c_str());
    }
    return ret;
}
