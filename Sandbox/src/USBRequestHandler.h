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
#include <map>

class USBRequestHandler{
private:
	static USBRequestHandler* instance_;
	std::map<unsigned int, boost::function<void (usb::urb*)> > handlerMap;
	USBRequestHandler();
	USBRequestHandler(USBRequestHandler& cpy);

	//handlers

	static void handleAddressRequest(usb::urb* req);
	static void handleConfigurationRequest(usb::urb* req);
	static void handleInterfaceRequest(usb::urb* req);
	static void handleDescriptorRequest(usb::urb* req);
	static void handleStatusRequest(usb::urb* req);
	static void justAck(usb::urb* req);
	static void handleFail(usb::urb* req,unsigned int r, unsigned int rt);

public:
	void handleUSBRequest(usb::urb* usb_request_to_process_);
	~USBRequestHandler();
	static USBRequestHandler* getInstance();

	static uint8_t* getStringDescriptorDataFromString(std::string to_convert);
};



#endif /* USBREQUESTHANDLER_H_ */
