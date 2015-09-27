#ifndef UARTDEVICETEST_H_
#define UARTDEVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class SampleTest: public CppUnit::TestCase{
	CPPUNIT_TEST_SUITE( SampleTest );
	CPPUNIT_TEST( testSomething );
//	CPPUNIT_TEST( testAddition );
	CPPUNIT_TEST_SUITE_END();

//	static CppUnit::TestSuite *suite();
private:
	StuffUnderTestClass* test_StuffUnderTestObject_;
public:
	  void setUp();
	  void tearDown();
	  void testSomething();
}
#endif /* UARTDEVICETEST_H_ */
