#ifndef DATABASEXMLHANDLERTEST_H_
#define DATABASEXMLHANDLERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <libxml++/libxml++.h>

class DatabaseXMLHandler;

class DatabaseXMLHandlerTest:public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE (DatabaseXMLHandlerTest);
    CPPUNIT_TEST (testHandle);
    CPPUNIT_TEST (testWriteHandle);
    CPPUNIT_TEST_SUITE_END();

    private:
      DatabaseXMLHandler* tested_handler_;
      xmlpp::Document* doc_;

    public:
      void setUp();
      void tearDown();
      void testHandle();
      void testWriteHandle();
};
CPPUNIT_TEST_SUITE_REGISTRATION (DatabaseXMLHandlerTest);
#endif /* DATABASEXMLHANDLERTEST_H_ */
