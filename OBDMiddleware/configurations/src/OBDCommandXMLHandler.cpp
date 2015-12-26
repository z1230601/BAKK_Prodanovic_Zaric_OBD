#include "OBDCommandXMLHandler.h"
#include "libxml++/libxml++.h"

OBDCommandXMLHandler::OBDCommandXMLHandler()
{

}

OBDCommandXMLHandler::~OBDCommandXMLHandler()
{

}

void OBDCommandXMLHandler::handleNode(xmlpp::Node* node)
{

    if(node->get_name().compare(VERSION_TAG) == 0)
    {
        current_elm_command_.version_ = getTextFromNode(node);
    }
}
