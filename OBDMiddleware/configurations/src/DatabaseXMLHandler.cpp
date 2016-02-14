#include "DatabaseXMLHandler.h"

DatabaseXMLHandler::DatabaseXMLHandler()
{
}

DatabaseXMLHandler::~DatabaseXMLHandler()
{
}

void DatabaseXMLHandler::handleNode(xmlpp::Node* node)
{
    if(is_writing_)
    {
        writeHandleNode(node);
    } else
    {
        readHandleNode(node);
    }
}

void DatabaseXMLHandler::writeHandleNode(xmlpp::Node* node)
{
    if(node->get_name().compare(ADDRESS_TAG) == 0)
    {
        setTextToNode(node, host_address_);
    }
    if(node->get_name().compare(USER_TAG) == 0)
    {
        setTextToNode(node, username_);
    }
    if(node->get_name().compare(PASSWORD_TAG) == 0)
    {
        setTextToNode(node, password_);
    }
    if(node->get_name().compare(DBNAME_TAG) == 0)
    {
        setTextToNode(node, dbname_);
    }
}

void DatabaseXMLHandler::readHandleNode(xmlpp::Node* node)
{
    if(node->get_name().compare(ADDRESS_TAG) == 0)
    {
        host_address_ = getTextFromNode(node);
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

void DatabaseXMLHandler::setHostAddress(std::string host_address) {
    host_address_ = host_address;
}


std::string DatabaseXMLHandler::getDBName()
{
    return dbname_;
}

void DatabaseXMLHandler::setDBName(std::string dbname) {
    dbname_ = dbname;
}


std::string DatabaseXMLHandler::getPassword()
{
    return password_;
}

void DatabaseXMLHandler::setPassword(std::string password) {
    password_ = password;
}


std::string DatabaseXMLHandler::getUsername()
{
    return username_;
}

void DatabaseXMLHandler::setUsername(std::string username) {
    username_ = username;
}
