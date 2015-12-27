#include "DefaultXMLHandler.h"

DefaultXMLHandler::DefaultXMLHandler()
{
}

DefaultXMLHandler::~DefaultXMLHandler()
{
}

std::string DefaultXMLHandler::getTextFromNode(xmlpp::Node* node)
{
    xmlpp::Node::NodeList text_list = node->get_children();
    if(text_list.size() == 1)
    {
        xmlpp::TextNode* text = dynamic_cast<xmlpp::TextNode*>(node
                ->get_first_child());
        if(text == NULL)
        {
            return "";
        }
        return std::string(text->get_content().c_str());
    }
    return "";
}

std::map<std::string, std::string> DefaultXMLHandler::getAttributesFromElement(
        xmlpp::Element* el)
{
    std::map<std::string, std::string> ret;
    std::list<xmlpp::Attribute*> list = el->get_attributes();
    for(xmlpp::Attribute* attr : list){
        ret[std::string(attr->get_name().c_str())] = std::string(attr->get_value().c_str());
    }
    return ret;
}
