/*
 * USBRequestHandler.h
 *
 *  Created on: Oct 4, 2015
 *      Author: zlatan
 */

#ifndef USBREQUESTHANDLER_H_
#define USBREQUESTHANDLER_H_

#include "libusb_vhci.h"
#include "boost/function.hpp"
#include "EmulatedDevice.h"
#include <map>

class USBRequestHandler{
private:
	static USBRequestHandler* instance_;

	std::map<unsigned int, boost::function<void (usb::urb*)> > handlerMap;
	USBRequestHandler();
	USBRequestHandler(USBRequestHandler& cpy);

	void setUpHandlerMap();
	static void copyIntoBufferAndAcknowledgeRequest(const uint8_t* to_copy, usb::urb* usb_request_to_process_, int descriptor_length_index = 0);
	//handlers
	static void (*device_handler_)(std::string &);

	static void handleAddressRequest(usb::urb* req);
	static void handleConfigurationRequest(usb::urb* req);
	static void handleInterfaceRequest(usb::urb* req);
	static void handleDescriptorRequest(usb::urb* req);
	static void handleGetStringDescriptorRequest(usb::urb* usb_request_to_process_);
	static void handleStatusRequest(usb::urb* req);
	static void justAck(usb::urb* req);
	static void handleFail(usb::urb* req,unsigned int r, unsigned int rt);


	//data handler
	static void handleBulkInRequest(usb::urb* req);
	static void handleBulkOutRequest(usb::urb* req);
public:
	static EmulatedDevice* device_representation_;
	static EmulatedDevice* getDevice();
	static void initCallback(void (*to_set)(std::string &));

	void handleUSBRequest(usb::urb* usb_request_to_process_);
	void handleBulkRequest(usb::urb* usb_request_to_process_);

	~USBRequestHandler();
	static USBRequestHandler* getInstance();
};



#endif /* USBREQUESTHANDLER_H_ */
