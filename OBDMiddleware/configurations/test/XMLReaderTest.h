#ifndef XMLREADERTEST_H_
#define XMLREADERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "../src/DefaultXMLHandler.h"

class MockHandlerReaderTest : public DefaultXMLHandler
{
    private:
        std::vector<std::string> containedTags{"address","password","user", "dbname", "text"};
        std::vector<std::string> notOccured{"address","password","user", "dbname", "text"};
    public:
        MockHandlerReaderTest();
        void handleNode(xmlpp::Node* node);

        std::vector<std::string> getNotOccured() const
        {
            return notOccured;
        }
};

class XMLReader;

class XMLReaderTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE (XMLReaderTest);
        CPPUNIT_TEST (testParseFile);CPPUNIT_TEST_SUITE_END();

    private:
        XMLReader* xmlreader_under_test_;
        MockHandlerReaderTest* mockhandler_;

    public:
        void setUp();
        void tearDown();
        void testParseFile();
};
CPPUNIT_TEST_SUITE_REGISTRATION (XMLReaderTest);

#endif /* XMLREADERTEST_H_ */
