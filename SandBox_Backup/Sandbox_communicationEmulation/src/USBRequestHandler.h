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
	std::map<unsigned int, boost::function<void (usb::urb*)> > handlerMap;
    EmulatedDevice* device_representation_;

	USBRequestHandler(USBRequestHandler& cpy);

	void copyIntoBufferAndAcknowledgeRequest(const uint8_t* to_copy, usb::urb* usb_request_to_process_, int descriptor_length_index = 0);
	//handlers

	void handleAddressRequest(usb::urb* req);
	void handleConfigurationRequest(usb::urb* req);
	void handleInterfaceRequest(usb::urb* req);
	void handleDescriptorRequest(usb::urb* req);
	void handleGetStringDescriptorRequest(usb::urb* usb_request_to_process_);
	void handleStatusRequest(usb::urb* req);
	void justAck(usb::urb* req);
	void handleFail(usb::urb* req,unsigned int r, unsigned int rt);


	//data handler
	void handleBulkInRequest(usb::urb* req);
	void handleBulkOutRequest(usb::urb* req);
public:
	USBRequestHandler();
	USBRequestHandler(void (*device_handler_)(std::string &));

	EmulatedDevice* getDevice();
	void initCallback(void (*to_set)(std::string &));

	void handleUSBRequest(usb::urb* usb_request_to_process_);
	void handleBulkRequest(usb::urb* usb_request_to_process_);

	~USBRequestHandler();
};


#endif /* USBREQUESTHANDLER_H_ */
