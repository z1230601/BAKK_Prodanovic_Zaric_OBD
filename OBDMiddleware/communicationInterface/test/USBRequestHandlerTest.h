/*
 * USBRequestHandlerTest.h
 *
 *  Created on: Oct 28, 2015
 *      Author: zlatan
 */

#ifndef USBREQUESTHANDLERTEST_H_
#define USBREQUESTHANDLERTEST_H_


#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>
#include "libusb_vhci.h"

class USBRequestHandlerTest: public CppUnit::TestCase{
	CPPUNIT_TEST_SUITE( USBRequestHandlerTest );
	CPPUNIT_TEST( testInit );
    CPPUNIT_TEST( testDescriptorRequest );

    CPPUNIT_TEST( testBulkInRequest );
    CPPUNIT_TEST( testBulkInBufferWrongRequest);
    CPPUNIT_TEST( testBulkOutRequest );

    CPPUNIT_TEST_SUITE_END();

private:
	usb::urb* test_request_;

public:
	void setUp();
	void tearDown();

	void testInit();
	void testDescriptorRequest();

	//data handler
	void testBulkInRequest();
	void testBulkInBufferWrongRequest();
	void testBulkOutRequest();
};
CPPUNIT_TEST_SUITE_REGISTRATION(USBRequestHandlerTest);
#endif /* USBREQUESTHANDLERTEST_H_ */
