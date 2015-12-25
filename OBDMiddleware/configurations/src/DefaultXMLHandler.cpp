/*
 * DefaultHandler.cpp
 *
 *  Created on: Dec 25, 2015
 *      Author: zlatan
 */

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
                dynamic_cast<xmlpp::TextNode*>(*text_list.begin());
        return std::string(text->get_content().c_str());
    }
    return "";
}
