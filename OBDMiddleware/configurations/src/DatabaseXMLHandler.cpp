#include "DatabaseXMLHandler.h"

DatabaseXMLHandler::DatabaseXMLHandler()
{
}

DatabaseXMLHandler::~DatabaseXMLHandler()
{
}

void DatabaseXMLHandler::handleNode(xmlpp::Node* node)
{
    if(node->get_name().compare(ADDRESS_TAG) == 0)
    {
        host_address_.append("tcp://");
        host_address_.append(getTextFromNode(node));
        host_address_.append(":3306");
    }
    if(node->get_name().compare(USER_TAG) == 0)
    {
        username_ = getTextFromNode(node);
    }
    if(node->get_name().compare(PASSWORD_TAG) == 0)
    {
        password_ = getTextFromNode(node);
    }
    if(node->get_name().compare(DBNAME_TAG) == 0)
    {
        dbname_ = getTextFromNode(node);
    }
}

std::string DatabaseXMLHandler::getHostAddress()
{
    return host_address_;
}

std::string DatabaseXMLHandler::getDBName(){
    return dbname_;
}

std::string DatabaseXMLHandler::getPassword(){
    return password_;
}

std::string DatabaseXMLHandler::getUsername(){
    return username_;
}
