#ifndef VALUEELMCOMMANDTEST_H_
#define VALUEELMCOMMANDTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class ValueElmCommand;

class ValueElmCommandTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE (SimpleElmCommandTest);
	CPPUNIT_TEST(testCommandWithValues);
//	CPPUNIT_TEST(testCommandConversionToSerial);
	CPPUNIT_TEST_SUITE_END();

private:
	ValueElmCommand* command_for_test_;

public:
	void setUp();
	void tearDown();
	void testCommandWithValues();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ValueElmCommandTest);

#endif /* VALUEELMCOMMANDTEST_H_ */
