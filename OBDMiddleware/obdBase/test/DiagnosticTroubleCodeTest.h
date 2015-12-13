#ifndef DIAGNOSTICTROUBLECODETEST_H_
#define DIAGNOSTICTROUBLECODETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class DiagnosticTroubleCode;

class DiagnosticTroubleCodeTest : public CppUnit::TestCase{
	CPPUNIT_TEST_SUITE (DiagnosticTroubleCodeTest);
//	CPPUNIT_TEST ();
	CPPUNIT_TEST(testConstruction);
	CPPUNIT_TEST(testConversion);
	CPPUNIT_TEST_SUITE_END();
private:
		DiagnosticTroubleCode* dtc_under_test_;

public:
	void setUp();
	void tearDown();
	void testConstruction();
	void testConversion();
};
CPPUNIT_TEST_SUITE_REGISTRATION (DiagnosticTroubleCodeTest);
#endif /* DIAGNOSTICTROUBLECODETEST_H_ */
