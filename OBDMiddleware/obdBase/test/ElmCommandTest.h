#ifndef ELMCOMMANDTEST_H_
#define ELMCOMMANDTEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class ElmCommand;

class ElmCommandTest: public CppUnit::TestCase {
	CPPUNIT_TEST_SUITE (ElmCommandTest);
	CPPUNIT_TEST(testCommandWithoutValue);
	CPPUNIT_TEST(testCommandWithOneValue);
	CPPUNIT_TEST(testCommandWithTwoDigitValue);
	CPPUNIT_TEST(testCommandWithThreeDigitValue);
	CPPUNIT_TEST(testCommandWithEightDigitValue);
	CPPUNIT_TEST(testInvalidValueString);
	CPPUNIT_TEST_SUITE_END();

private:
	ElmCommand* command_for_test_;

public:
	void setUp();
	void tearDown();
	void testCommandWithoutValue();
	void testCommandWithOneValue();
	void testCommandWithTwoDigitValue();
	void testCommandWithThreeDigitValue();
	void testCommandWithEightDigitValue();
	void testInvalidValueString();
};

CPPUNIT_TEST_SUITE_REGISTRATION(ElmCommandTest);

#endif /* ELMCOMMANDTEST_H_ */
