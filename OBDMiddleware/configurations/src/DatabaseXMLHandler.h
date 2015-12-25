/*
 * DatabaseXMLHandler.h
 *
 *  Created on: Dec 25, 2015
 *      Author: zlatan
 */

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

        std::string getHostAddress();
        std::string getDBName();
        std::string getPassword();
        std::string getUsername();
};

#endif /* DATABASEXMLHANDLER_H_ */
