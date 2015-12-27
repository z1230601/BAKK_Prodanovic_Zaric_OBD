#ifndef OBDCOMMANDXMLHANDLERTEST_H_
#define OBDCOMMANDXMLHANDLERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "libxml++/libxml++.h"

#include "../src/OBDCommandXMLHandler.h"
class OBDCommandXMLHandler;

class OBDCommandXMLHandlerTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE(OBDCommandXMLHandlerTest);
    CPPUNIT_TEST(testServiceModeParse);
    CPPUNIT_TEST_SUITE_END();

    private:
    OBDCommandXMLHandler* handler_for_test_;
    xmlpp::Document* doc_;

    public:
    void setUp();
    void tearDown();
    void testServiceModeParse();
};
CPPUNIT_TEST_SUITE_REGISTRATION (OBDCommandXMLHandlerTest);
#endif /* OBDCOMMANDXMLHANDLERTEST_H_ */
