#ifndef SIMPLEELMCOMMANDTEST_H_
#define SIMPLEELMCOMMANDTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class SimpleElmCommand;

class SimpleElmCommandTest : public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE (SimpleElmCommandTest);
	CPPUNIT_TEST(testSimpleCommandCreation);
	CPPUNIT_TEST(testCommandConversionToSerial);
//	CPPUNIT_TEST(testCommandWithValues);
	CPPUNIT_TEST_SUITE_END();

private:
	SimpleElmCommand* command_for_test_;

public:
	void setUp();
	void tearDown();
	void testSimpleCommandCreation();
	void testCommandConversionToSerial();
};

CPPUNIT_TEST_SUITE_REGISTRATION (SimpleElmCommandTest);

#endif /* SIMPLEELMCOMMANDTEST_H_ */
