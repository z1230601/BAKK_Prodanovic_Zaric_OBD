#include "DefaultXMLHandler.h"

DefaultXMLHandler::DefaultXMLHandler() : is_writing_(false)
{
}

DefaultXMLHandler::~DefaultXMLHandler()
{
}

void DefaultXMLHandler::setWriting(bool writing) {
    is_writing_ = writing;
}

std::string DefaultXMLHandler::getTextFromNode(xmlpp::Node* node)
{
    xmlpp::Element* node_as_element = dynamic_cast<xmlpp::Element*>(node);
    if(node_as_element == NULL)
    {
        return "";
    }

    xmlpp::TextNode* text = node_as_element->get_child_text();
    if(text == NULL)
    {
        return "";
    }
    return std::string(text->get_content().c_str());
}

void DefaultXMLHandler::setTextToNode(xmlpp::Node* node, std::string new_text)
{
    xmlpp::Element* node_as_element = dynamic_cast<xmlpp::Element*>(node);
    if(node_as_element == NULL)
    {
        return;
    }

    node_as_element->set_child_text(new_text);
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
