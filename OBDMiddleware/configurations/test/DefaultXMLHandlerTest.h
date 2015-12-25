#ifndef DEFAULTXMLHANDLERTEST_H_
#define DEFAULTXMLHANDLERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "../src/DefaultXMLHandler.h"

class MockHandlerHandlerTest : public DefaultXMLHandler
{
    private:
    public:
        MockHandlerHandlerTest();
        void handleNode(xmlpp::Node* node);
        std::string getTextFromNodeForTest(xmlpp::Node* node);
};

class DefaultXMLHandlerTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE (DefaultXMLHandlerTest);
        CPPUNIT_TEST (testGetTextNode);
        CPPUNIT_TEST (testWrongNode);
        CPPUNIT_TEST_SUITE_END();

    private:
        xmlpp::Document* doc;
        xmlpp::Node* node_for_test_;

    public:
        void setUp();
        void tearDown();
        void testGetTextNode();
        void testWrongNode();
};
CPPUNIT_TEST_SUITE_REGISTRATION (DefaultXMLHandlerTest);

#endif /* DEFAULTXMLHANDLERTEST_H_ */
