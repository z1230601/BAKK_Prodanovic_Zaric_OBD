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
        void setWriting(bool writing);

    protected:
        std::string getTextFromNode(xmlpp::Node* node);
        void setTextToNode(xmlpp::Node* node, std::string new_text);
        std::map<std::string, std::string> getAttributesFromElement(xmlpp::Element* el);

        bool is_writing_;
};

#endif /* DEFAULTHANDLER_H_ */
