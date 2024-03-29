#ifndef UARTDEVICETEST_H_
#define UARTDEVICETEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class UartDevice;

class UartDeviceTest: public CppUnit::TestCase{
	CPPUNIT_TEST_SUITE( UartDeviceTest );
	CPPUNIT_TEST( testRead );
//	CPPUNIT_TEST( testAnotherthing );
	CPPUNIT_TEST_SUITE_END();


//	static CppUnit::TestSuite *suite();
private:
	UartDevice* test_device_;
public:
	  void setUp();
	  void tearDown();
	  void testRead();
};
CPPUNIT_TEST_SUITE_REGISTRATION(UartDeviceTest);
#endif /* UARTDEVICETEST_H_ */
