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
EmulatedDevice* USBRequestHandler::device_representation_;
void (*USBRequestHandler::device_handler_)(std::string &);

USBRequestHandler* USBRequestHandler::getInstance() {
	if (instance_ == NULL) {
		instance_ = new USBRequestHandler();
	}
	return instance_;
}

USBRequestHandler::~USBRequestHandler(){
	delete device_representation_;
}
void printRequest(usb::urb* usb_request){

	std::cout << "handle: " << usb_request->get_handle() <<  std::endl
			<< "type: " << usb_request->get_type() << std::endl
			<< "buffer_length: " << usb_request->get_buffer_length() << std::endl
			<< "buffer: " << usb_request->get_buffer()<< std::endl
			<< "iso_packet_count: " << usb_request->get_iso_packet_count() << std::endl
			<< "buffer_actual: " << usb_request->get_buffer_actual() << std::endl
			<< "status: " << usb_request->get_status() << std::endl
			<< "error_count: " << usb_request->get_iso_error_count() << std::endl
			<< "flags: " << usb_request->get_flags() << std::endl
			<< "interval: " << usb_request->get_interval() << std::endl
			<< "device address: " << usb_request->get_device_address() << std::endl
			<< "endpoint address: " << usb_request->get_endpoint_address() << std::endl
			<< "bmRequestType: " << usb_request->get_bmRequestType() << std::endl
			<< "bRequest: " << usb_request->get_bRequest() << std::endl
			<< "wValue: " << usb_request->get_wValue() << std::endl
			<< "wIndex: " << usb_request->get_wIndex() << std::endl
			<< "wLength: " << usb_request->get_wLength() << std::endl;
}
void USBRequestHandler::handleUSBRequest(usb::urb* usb_request_to_process_) {
//	printRequest(usb_request_to_process_);
	unsigned int rt(usb_request_to_process_->get_bmRequestType());
	unsigned int r(usb_request_to_process_->get_bRequest());

	unsigned int key = rt;
	key = key << 8;
	key = key | r;

	if (instance_->handlerMap.find(key) != handlerMap.end()) {
		instance_->handlerMap.at(key)(usb_request_to_process_);
	} else {
		handleFail(usb_request_to_process_, r, rt);
	}
}

void USBRequestHandler::initCallback(void (*to_set)(std::string &)){
	device_handler_ = to_set;
}

USBRequestHandler::USBRequestHandler() {
	if(device_handler_ == NULL){
		device_representation_ = new EmulatedDevice();
	}else{
		device_representation_ = new EmulatedDevice(device_handler_);
	}
	setUpHandlerMap();
}

void USBRequestHandler::setUpHandlerMap(){

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

	// vendor specified handlers
	handlerMap.insert(
			std::pair<unsigned int, boost::function<void(usb::urb*)>>(
						0x0400 | URB_RQ_GET_STATUS, &handleStatusRequest));
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

	switch (usb_request_to_process_->get_wValue() >> 8) {
	case 1:
		std::cout << "DEVICE_DESCRIPTOR" << std::endl;
		copyIntoBufferAndAcknowledgeRequest(
				device_representation_->getDeviceDescriptor(),
				usb_request_to_process_);
		break;
	case 2:
		std::cout << "CONFIGURATION_DESCRIPTOR" << std::endl;
		copyIntoBufferAndAcknowledgeRequest(
				device_representation_->getConfigurationDescriptor(),
				usb_request_to_process_, 2);
		break;
	case 3:
		handleGetStringDescriptorRequest(usb_request_to_process_);
		break;
	default:
		usb_request_to_process_->stall();
		break;
	}
}

void USBRequestHandler::handleGetStringDescriptorRequest(
		usb::urb* usb_request_to_process_) {
	std::cout << "STRING_DESCRIPTOR: "
			<< (usb_request_to_process_->get_wValue() & 0xff) << std::endl;
	int id = usb_request_to_process_->get_wValue() & 0xff;
	if (id == 0) {
		copyIntoBufferAndAcknowledgeRequest(
				device_representation_->getLanguageDescriptor(),
				usb_request_to_process_);
	} else {
		try {
			uint8_t* str_desc =
					device_representation_->getStringDescriptorFromId(id);
			copyIntoBufferAndAcknowledgeRequest(str_desc,
					usb_request_to_process_);
			std::free(str_desc);
		} catch (std::runtime_error e) {
			usb_request_to_process_->stall();
		}
	}
}

void USBRequestHandler::copyIntoBufferAndAcknowledgeRequest(
		const uint8_t* desc, usb::urb* usb_request_to_process_, int descriptor_length_index) {
	int request_length(usb_request_to_process_->get_wLength());
	if (desc[descriptor_length_index] < request_length)
		request_length = desc[descriptor_length_index];
	std::copy(desc, desc + request_length, usb_request_to_process_->get_buffer());
	usb_request_to_process_->set_buffer_actual(request_length);
	usb_request_to_process_->ack();
}

void USBRequestHandler::handleFail(usb::urb* usb_request_to_process_,
		unsigned int r, unsigned int rt) {
	if (what.find(r) != what.end()) {
		std::cout << "Not recognized: bmRequestType: " << std::bitset<8>(rt) << " bRequest: " << (int) r
				<< std::dec << " " << what.at(r) << std::endl;
		unsigned int key = rt;
		key = key << 8;
		key = key | r;

		std::cout << "key: " << std::hex << key << std::endl;
	} else {
		std::cout << "Not recognized: bmRequestType: " << std::bitset<8>(rt) << " bRequest: " << (int) r << std::endl;
	}
	usb_request_to_process_->stall();
}

void USBRequestHandler::justAck(usb::urb* req) {
	req->ack();
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

void USBRequestHandler::handleBulkRequest(usb::urb* usb_request_to_process_) {
	if(usb_request_to_process_->is_in()){
		handleBulkInRequest(usb_request_to_process_);
	}else{
		handleBulkOutRequest(usb_request_to_process_);
	}
}

void USBRequestHandler::handleBulkInRequest(usb::urb* usb_request_to_process_){
	//Use Emulated Device here!
	//USB is host centric meaning bulk in request a polling request for asking if new data is available at the hosts input

	uint8_t* buff = usb_request_to_process_->get_buffer();
	uint8_t* buff2 = device_representation_->getCurrentDataToSendAsUint8Array();
	int length = buff2[0];
	std::copy(buff2, buff2 + length, buff);
	buff[0] = 0x01;
	buff[1] = 0x60;
	usb_request_to_process_->set_buffer_actual(length);
	usb_request_to_process_->ack();
}

void USBRequestHandler::handleBulkOutRequest(usb::urb* usb_request_to_process){
	//Use Emulated Device here!
//	usb_request_to_process->ack();
	device_representation_->setRecievedData(usb_request_to_process->get_buffer(), usb_request_to_process->get_buffer_length());
}

EmulatedDevice* USBRequestHandler::getDevice() {
	return device_representation_;
}
