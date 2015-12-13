/*
 * USBRequestHandlerTest.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: zlatan
 */
#include "USBRequestHandlerTest.h"
#include "../src/USBRequestHandler.h"
//#include "../src/EmulatedDevice.h"
#include "libusb_vhci.h"

void testCallback(std::string & command){
	std::cout << "Enter testcallback with : "<< command << "\n";
	if(command == "atz"){
		USBRequestHandler::getDevice()->addAnswerToQueue("answer");
	}else{
		CPPUNIT_FAIL("Wrong command parsed");
	}
}


void USBRequestHandlerTest::setUp(){
//	test_request_ =
	USBRequestHandler::initCallback(&testCallback);
}

void USBRequestHandlerTest::tearDown(){
	delete test_request_;
}


void USBRequestHandlerTest::testInit(){
	USBRequestHandler::initCallback(&testCallback);
	CPPUNIT_ASSERT(USBRequestHandler::getDevice() == NULL);
	USBRequestHandler::getInstance();
	CPPUNIT_ASSERT(USBRequestHandler::getDevice() != NULL);
}

//data handler
void USBRequestHandlerTest::testBulkInRequest() {
	std::cout << "Test BULK IN\n";
	uint8_t buffer[2];
	try {
		usb::urb* request = new usb::urb(false, usb::urb_type_bulk, 2, buffer,
				false, 0, NULL, true, 0, USB_VHCI_STATUS_PENDING, 0, 0x0, 0, 0,
				0x80, 0x0, 0x0, 0x0, 0x0, 0);

		CPPUNIT_ASSERT(request->get_status() != USB_VHCI_STATUS_SUCCESS);
		USBRequestHandler::getInstance()->handleBulkRequest(request);
		CPPUNIT_ASSERT(request->get_status() == USB_VHCI_STATUS_SUCCESS);
		CPPUNIT_ASSERT(request->get_buffer_actual() == 2);
		CPPUNIT_ASSERT(request->get_buffer()[0] == 0x01);
		CPPUNIT_ASSERT(request->get_buffer()[1] = 0x60);
	} catch (std::exception &e) {
		CPPUNIT_FAIL(e.what());
	}
}

void USBRequestHandlerTest::testBulkInBufferWrongRequest() {
	std::cout << "Test BULK IN fail\n";
	uint8_t buffer[2];
	try {
		usb::urb* request = new usb::urb(false, usb::urb_type_bulk, 0, buffer,
				false, 0, NULL, true, 0, USB_VHCI_STATUS_PENDING, 0, 0x0, 0, 0,
				0x80, 0x0, 0x0, 0x0, 0x0, 0);

		CPPUNIT_ASSERT(request->get_status() != USB_VHCI_STATUS_SUCCESS);
		USBRequestHandler::getInstance()->handleBulkRequest(request);
		CPPUNIT_ASSERT(request->get_status() == USB_VHCI_STATUS_STALL);
		CPPUNIT_ASSERT(request->get_buffer_actual() == 0);
		CPPUNIT_ASSERT(request->get_buffer() == NULL);
	} catch (std::exception &e) {
		CPPUNIT_FAIL(e.what());
	}
}

void USBRequestHandlerTest::testBulkOutRequest() {
	std::cout << "Test BULK OUT\n";
	uint8_t command[] = {'a', 't', 'z', 0x0d};


	for(int i = 0; i < 4; i++){
		usb::urb* request = new usb::urb(false, usb::urb_type_bulk, 1, &command[i],
				false, 0, NULL, true, 0, USB_VHCI_STATUS_PENDING, 0, 0x0, 0, 0,
				0x02, 0x0, 0x0, 0x0, 0x0, 0);
		CPPUNIT_ASSERT(request->get_status() != USB_VHCI_STATUS_SUCCESS);
		USBRequestHandler::getInstance()->handleBulkRequest(request);
		CPPUNIT_ASSERT(request->get_status() == USB_VHCI_STATUS_SUCCESS);
	}

	std::string expected = "answer\n\r>";
	std::string result = USBRequestHandler::getInstance()->device_representation_->getCurrentSendBuffer();
	CPPUNIT_ASSERT_EQUAL(expected,result);
}

void USBRequestHandlerTest::testDescriptorRequest(){
//	usb::urb* request = new usb::urb(false, usb::urb_type_control, 0, NULL,
//					false, 0, NULL, true, 0, USB_VHCI_STATUS_PENDING, 0, 0x0, 0, 0,
//					0x02, 0x0, 0x0, 0x0, 0x0, 0);
}
