#ifndef XMLREADER_H_
#define XMLREADER_H_

#include "DefaultXMLHandler.h"

class XMLReader
{
        //ensure constructors are not implemented by compiler
        XMLReader() = delete;
        XMLReader(XMLReader &o) = delete;
        XMLReader(XMLReader &&o) = delete;

    private:
        DefaultXMLHandler* handler_;

        void iterateChildren(const xmlpp::Node* parent);
    public:
        XMLReader(DefaultXMLHandler* handler);
        virtual ~XMLReader();

        bool parseFile(std::string configurationFile);
};

#endif /* XMLREADER_H_ */
