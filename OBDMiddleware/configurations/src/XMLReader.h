#ifndef XMLREADER_H_
#define XMLREADER_H_

#include "DefaultXMLHandler.h"
#include "libxml++/libxml++.h"

class XMLReader
{
        //ensure constructors are not implmented by compiler
        XMLReader() = delete;
        XMLReader(XMLReader &o) = delete;
        XMLReader(XMLReader &&o) = delete;

    private:
        DefaultXMLHandler* handler_;
    public:
        XMLReader(DefaultXMLHandler* handler);
        virtual ~XMLReader();

        bool parseFile(std::string configurationFile);
};

#endif /* XMLREADER_H_ */
