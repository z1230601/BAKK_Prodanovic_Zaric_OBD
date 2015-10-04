/*
 * USBRequestHandler.cpp
 *
 *  Created on: Oct 4, 2015
 *      Author: zlatan
 */
#include "USBRequestHandler.h"
#include "USBEmulationConstants.h"

#include <iostream>
#include <bitset>
#include <iomanip>

USBRequestHandler* USBRequestHandler::instance_;

USBRequestHandler* USBRequestHandler::getInstance() {
	if (instance_ == NULL) {
		instance_ = new USBRequestHandler();
	}
	return instance_;
}

void USBRequestHandler::handleUSBRequest(usb::urb* usb_request_to_process_) {
	unsigned int rt(usb_request_to_process_->get_bmRequestType());
	unsigned int r(usb_request_to_process_->get_bRequest());

	unsigned int key = rt;
	key = key << 8;
	key = key | r;

//	std::cout << "key: " << std::hex << key << " " << (int) rt << " " << (int) r << std::endl;
	if(instance_->handlerMap.find(key) != handlerMap.end()){
		instance_->handlerMap.at(key)(usb_request_to_process_);
	} else {
		handleFail(usb_request_to_process_, r, rt);
	}
}

USBRequestHandler::USBRequestHandler() {
	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x0000 | URB_RQ_SET_ADDRESS ,
			&handleAddressRequest));
	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x0000 | URB_RQ_SET_CONFIGURATION ,
			&handleConfigurationRequest));
	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x0000 | URB_RQ_SET_INTERFACE ,
			&handleInterfaceRequest));
	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x8000 | URB_RQ_GET_DESCRIPTOR ,
			&handleDescriptorRequest));
}

void USBRequestHandler::handleAddressRequest(usb::urb* req) {
	std::cout << "SET_ADDRESS" << std::endl;
	req->ack();
}
void USBRequestHandler::handleConfigurationRequest(usb::urb* req) {
	std::cout << "SET_CONFIGURATION" << std::endl;
	req->ack();
}
void USBRequestHandler::handleInterfaceRequest(usb::urb* req) {
	std::cout << "SET_INTERFACE" << std::endl;
	req->ack();
}
void USBRequestHandler::handleDescriptorRequest(
		usb::urb* usb_request_to_process_) {
	std::cout << "GET_DESCRIPTOR" << std::endl;
	int l(usb_request_to_process_->get_wLength());
	uint8_t* buffer(usb_request_to_process_->get_buffer());
	switch (usb_request_to_process_->get_wValue() >> 8) {
	case 1:
		std::cout << "DEVICE_DESCRIPTOR" << std::endl;
		if (dev_desc[0] < l)
			l = dev_desc[0];
		std::copy(dev_desc, dev_desc + l, buffer);
		usb_request_to_process_->set_buffer_actual(l);
		usb_request_to_process_->ack();
		break;
	case 2:
		std::cout << "CONFIGURATION_DESCRIPTOR" << std::endl;
		if (conf_desc[2] < l)
			l = conf_desc[2];
		std::copy(conf_desc, conf_desc + l, buffer);
		usb_request_to_process_->set_buffer_actual(l);
		usb_request_to_process_->ack();
		break;
	case 3:
		std::cout << "STRING_DESCRIPTOR" << std::endl;
		switch (usb_request_to_process_->get_wValue() & 0xff) {
		case 0:
			if (str0_desc[0] < l)
				l = str0_desc[0];
			std::copy(str0_desc, str0_desc + l, buffer);
			usb_request_to_process_->set_buffer_actual(l);
			usb_request_to_process_->ack();
			break;
		case 1:
			if (str1_desc[0] < l)
				l = str1_desc[0];
			std::copy(str1_desc, str1_desc + l, buffer);
			usb_request_to_process_->set_buffer_actual(l);
			usb_request_to_process_->ack();
			break;
		default:
			usb_request_to_process_->stall();
			break;
		}
	default:
		usb_request_to_process_->stall();
		break;
	}
}

void USBRequestHandler::handleFail(usb::urb* usb_request_to_process_, unsigned int r, unsigned int rt){
	if (what.find(r) != what.end()) {
		std::cout << "Not recognized: " << std::bitset<8>(rt) << " "
				<< (int) r << std::dec << " " << what.at(r) << std::endl;
	} else {
		std::cout << "Not recognized: " << (int) r << std::endl;
	}
	usb_request_to_process_->stall();
}
