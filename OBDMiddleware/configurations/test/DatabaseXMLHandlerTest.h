#ifndef DATABASEXMLHANDLERTEST_H_
#define DATABASEXMLHANDLERTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include <libxml++/libxml++.h>
#include <string>

class DatabaseXMLHandler;

class DatabaseXMLHandlerTest:public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE (DatabaseXMLHandlerTest);
    CPPUNIT_TEST (testHandle);
    CPPUNIT_TEST_SUITE_END();

    private:
      DatabaseXMLHandler* tested_handler_;
      xmlpp::Document* doc_;

      std::string expected_address  = "testAddress";
      std::string expected_user = "testUser";
      std::string expected_password = "testPw";
      std::string expected_db_name = "testDBName";
    public:
      void setUp();
      void tearDown();
      void testHandle();
};
CPPUNIT_TEST_SUITE_REGISTRATION (DatabaseXMLHandlerTest);
#endif /* DATABASEXMLHANDLERTEST_H_ */
