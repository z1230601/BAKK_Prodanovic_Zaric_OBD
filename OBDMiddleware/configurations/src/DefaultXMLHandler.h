#ifndef DEFAULTHANDLER_H_
#define DEFAULTHANDLER_H_

#include <libxml++/libxml++.h>
#include <map>
#include <string>

class DefaultXMLHandler
{
    public:
        DefaultXMLHandler();
        virtual ~DefaultXMLHandler();

        virtual void handleNode(xmlpp::Node* node) = 0;

    protected:
        std::string getTextFromNode(xmlpp::Node* node);
        std::map<std::string, std::string> getAttributesFromElement(xmlpp::Element* el);
};

#endif /* DEFAULTHANDLER_H_ */
