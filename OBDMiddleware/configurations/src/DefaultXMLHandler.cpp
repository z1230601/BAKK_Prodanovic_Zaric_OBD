#include "DefaultXMLHandler.h"

DefaultXMLHandler::DefaultXMLHandler()
{
}

DefaultXMLHandler::~DefaultXMLHandler()
{
}

std::string DefaultXMLHandler::getTextFromNode(xmlpp::Node* node) {
    xmlpp::Node::NodeList text_list = node->get_children();
    if (text_list.size() == 1) {
        xmlpp::TextNode* text =
                dynamic_cast<xmlpp::TextNode*>(node->get_first_child());
        if(text == NULL){
            return "";
        }
        return std::string(text->get_content().c_str());
    }
    return "";
}
