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
#include <cstdlib>

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
	if (instance_->handlerMap.find(key) != handlerMap.end()) {
		instance_->handlerMap.at(key)(usb_request_to_process_);
	} else {
		handleFail(usb_request_to_process_, r, rt);
	}
}

USBRequestHandler::USBRequestHandler() {
	handlerMap.insert(
			std::pair<unsigned int, boost::function<void(usb::urb*)>>(
					0x0000 | URB_RQ_SET_ADDRESS, &handleAddressRequest));
	handlerMap.insert(
			std::pair<unsigned int, boost::function<void(usb::urb*)>>(
					0x0000 | URB_RQ_SET_CONFIGURATION,
					&handleConfigurationRequest));
	handlerMap.insert(
			std::pair<unsigned int, boost::function<void(usb::urb*)>>(
					0x0000 | URB_RQ_SET_INTERFACE, &handleInterfaceRequest));
	handlerMap.insert(
			std::pair<unsigned int, boost::function<void(usb::urb*)>>(
					0x8000 | URB_RQ_GET_DESCRIPTOR, &handleDescriptorRequest));
	handlerMap.insert(
			std::pair<unsigned int, boost::function<void(usb::urb*)>>(
			0x8000 | URB_RQ_GET_STATUS, &handleStatusRequest));
//	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0xC00A ,
//			&justAck));
//	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0xC005 ,
//				&justAck));
//	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x4000 ,
//					&justAck));
//	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x4009 ,
//					&justAck));
//	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x4003 ,
//						&justAck));
//	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x4001 ,
//						&justAck));
//	handlerMap.insert(std::pair<unsigned int, boost::function<void (usb::urb*)>>(0x4009 ,
//						&justAck));
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
	std::cout << "Language is: " << usb_request_to_process_->get_wIndex()
			<< std::endl;
	int l(usb_request_to_process_->get_wLength());

	uint8_t* buffer(usb_request_to_process_->get_buffer());
	std::cout << "requesting Descriptor: "
			<< (usb_request_to_process_->get_wValue() >> 8) << " Length: " << l
			<< std::endl;
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
		std::cout << "STRING_DESCRIPTOR: "
				<< (usb_request_to_process_->get_wValue() & 0xff) << std::endl;

		switch (usb_request_to_process_->get_wValue() & 0xff) {
		case 0:
			if (selectable_languages[0] < l)
				l = selectable_languages[0];
			std::copy(selectable_languages, selectable_languages + l, buffer);
			usb_request_to_process_->set_buffer_actual(l);
			usb_request_to_process_->ack();
			break;
		case 1: {
			uint8_t* str1_desc = getStringDescriptorDataFromString(string_id1);
			if (str1_desc[0] < l)
				l = str1_desc[0];
			std::copy(str1_desc, str1_desc + l, buffer);

			usb_request_to_process_->set_buffer_actual(l);
			usb_request_to_process_->ack();
			std::free(str1_desc);
			break;
		}
		case 2: {
			uint8_t* str2_desc = getStringDescriptorDataFromString(string_id2);
			if (str2_desc[0] < l)
				l = str2_desc[0];
			std::copy(str2_desc, str2_desc + l, buffer);
			std::cout << "As String: \n";
			for (int i = 2; i < l; i++) {
				std::cout << (char) str2_desc[i];
			}
			std::cout << std::endl;
			usb_request_to_process_->set_buffer_actual(l);
			usb_request_to_process_->ack();
			std::free(str2_desc);
			break;
		}
		case 3: {
			uint8_t* str3_desc = getStringDescriptorDataFromString(string_id3);
			if (str3_desc[0] < l)
				l = str3_desc[0];
			std::copy(str3_desc, str3_desc + l, buffer);
			usb_request_to_process_->set_buffer_actual(l);
			usb_request_to_process_->ack();
			std::free(str3_desc);
			break;
		}
		default:
			usb_request_to_process_->stall();
			break;
		}
		break;
	case 6: {
		uint8_t* str1_desc = getStringDescriptorDataFromString(string_id1);
		if (str1_desc[0] < l)
			l = str1_desc[0];
		std::copy(str1_desc, str1_desc + l, buffer);
		usb_request_to_process_->set_buffer_actual(l);
		usb_request_to_process_->ack();
		std::free(str1_desc);
		break;
	}
	default:
		usb_request_to_process_->stall();
		break;
	}
}

void USBRequestHandler::handleFail(usb::urb* usb_request_to_process_,
		unsigned int r, unsigned int rt) {
	if (what.find(r) != what.end()) {
		std::cout << "Not recognized: " << std::bitset<8>(rt) << " " << (int) r
				<< std::dec << " " << what.at(r) << std::endl;
		unsigned int key = rt;
		key = key << 8;
		key = key | r;

		std::cout << "key: " << std::hex << key << std::endl;
	} else {
		std::cout << "Not recognized: " << (int) r << std::endl;
	}
	usb_request_to_process_->stall();
}

void USBRequestHandler::justAck(usb::urb* req) {
	req->ack();
}

uint8_t* USBRequestHandler::getStringDescriptorDataFromString(const std::string to_convert){
	unsigned int length = 2 + to_convert.length()*2;
	uint8_t* converted = (uint8_t*) std::malloc(length * sizeof(uint8_t));

	converted[0] = length;
	converted[1] = 3;
	int converted_index = 2;
	for(unsigned int i=0; i < to_convert.length();i++){
		converted[converted_index] = (uint8_t) to_convert.at(i);
		converted_index++;
		converted[converted_index] = 0;
		converted_index++;
	}
	return converted;
}

void USBRequestHandler::handleStatusRequest(usb::urb* req){
	uint8_t* response = req->get_buffer();
	if(req->get_wLength() == 2){
		response[0]=0;
		response[1]=0;
	}

	req->set_buffer_actual(2);
	req->ack();
}
