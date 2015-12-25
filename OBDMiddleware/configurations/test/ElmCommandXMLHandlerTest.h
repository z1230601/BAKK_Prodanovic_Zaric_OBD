#ifndef ELMCOMMANDXMLHANDLERTEST_H_
#define ELMCOMMANDXMLHANDLERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "libxml++/libxml++.h"

#include "../src/ElmCommandXMLHandler.h"
class ElmCommandXMLHandler;
class ElmCommandXMLHandlerTest : public CppUnit::TestCase
{
        CPPUNIT_TEST_SUITE (ElmCommandXMLHandlerTest);
        CPPUNIT_TEST(testHandle);
        CPPUNIT_TEST (testHandle);CPPUNIT_TEST_SUITE_END();
    private:
        ElmCommandXMLHandler* tested_handler_;
        xmlpp::Document* doc_;

        void iterateChildren(const xmlpp::Node* parent);
    public:
        void setUp();
        void tearDown();
        void testHandle();
};
CPPUNIT_TEST_SUITE_REGISTRATION (ElmCommandXMLHandlerTest);
#endif /* ELMCOMMANDXMLHANDLERTEST_H_ */
