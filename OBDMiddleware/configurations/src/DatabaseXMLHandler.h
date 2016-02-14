#ifndef DATABASEXMLHANDLER_H_
#define DATABASEXMLHANDLER_H_

#include "DefaultXMLHandler.h"
#include <libxml++/libxml++.h>

#define ADDRESS_TAG "address"
#define USER_TAG "user"
#define PASSWORD_TAG "password"
#define DBNAME_TAG "dbname"

class DatabaseXMLHandler:public DefaultXMLHandler
{
    private:
        std::string host_address_;
        std::string username_;
        std::string password_;
        std::string dbname_;

    public:
        DatabaseXMLHandler();
        virtual ~DatabaseXMLHandler();

        void handleNode(xmlpp::Node* node);
        void writeHandleNode(xmlpp::Node* node);
        void readHandleNode(xmlpp::Node* node);

        std::string getHostAddress();
        void setHostAddress(std::string host_address);

        std::string getDBName();
        void setDBName(std::string dbname);

        std::string getPassword();
        void setPassword(std::string password);

        std::string getUsername();
        void setUsername(std::string username);
};

#endif /* DATABASEXMLHANDLER_H_ */
