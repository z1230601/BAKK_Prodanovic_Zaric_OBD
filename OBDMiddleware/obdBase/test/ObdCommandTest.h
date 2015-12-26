#ifndef OBDCOMMANDTEST_H_
#define OBDCOMMANDTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class ObdCommand;

class ObdCommandTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE (ObdCommandTest);
    CPPUNIT_TEST (test);
    CPPUNIT_TEST_SUITE_END();

    private:
    ObdCommand* obdcommand_for_test_;

    public:
    void setUp();
    void tearDown();
    void test();
};
CPPUNIT_TEST_SUITE_REGISTRATION (ObdCommandTest);
#endif /* OBDCOMMANDTEST_H_ */
