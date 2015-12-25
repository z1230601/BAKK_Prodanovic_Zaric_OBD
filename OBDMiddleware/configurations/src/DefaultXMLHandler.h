/*
 * DefaultHandler.h
 *
 *  Created on: Dec 25, 2015
 *      Author: zlatan
 */

#ifndef DEFAULTHANDLER_H_
#define DEFAULTHANDLER_H_

#include <libxml++/libxml++.h>

class DefaultXMLHandler
{
    public:
        DefaultXMLHandler();
        virtual ~DefaultXMLHandler();

        virtual void handleNode(xmlpp::Node* node) = 0;
    protected:
        std::string getTextFromNode(xmlpp::Node* node);
};

#endif /* DEFAULTHANDLER_H_ */
