#ifndef XMLWRITER_H_
#define XMLWRITER_H_

#include "DefaultXMLHandler.h"

class XMLWriter
{
        //ensure constructors are not implemented by compiler
        XMLWriter() = delete;
        XMLWriter(XMLWriter &o) = delete;
        XMLWriter(XMLWriter &&o) = delete;

    private:
        DefaultXMLHandler* handler_;

        void iterateChildren(const xmlpp::Node* parent);
    public:
        XMLWriter(DefaultXMLHandler* handler);
        virtual ~XMLWriter();

        bool writeFile(std::string configurationFile);
};

#endif /* XMLWRITER_H_ */
