/*
 * EmulatedDevice.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: zlatan
 */

#include <cstdlib>
#include <iostream>
#include "EmulatedDevice.h"
#include "USBRequestHandler.h"

EmulatedDevice::EmulatedDevice(){
	initStringDescriptorMapping();
	command_received_callback_ = NULL;
}

EmulatedDevice::EmulatedDevice(boost::function<void (std::string)> const &to_set){
	initStringDescriptorMapping();
	command_received_callback_ = to_set;
}

EmulatedDevice::EmulatedDevice(void (*to_set)(std::string &)){
	initStringDescriptorMapping();
	command_received_callback_ = to_set;
}

EmulatedDevice::~EmulatedDevice(){

}

void EmulatedDevice::initStringDescriptorMapping(){
	id_string_descriptor_mapping_.insert(std::make_pair(1,"FTDI"));
	id_string_descriptor_mapping_.insert(std::make_pair(2,"FT232R USB UART"));
	id_string_descriptor_mapping_.insert(std::make_pair(3, "A7030PE3"));
	id_string_descriptor_mapping_.insert(std::make_pair(6, "FTDI"));
	current_language_ = laguanges_["ENGLISH"];
}

uint8_t* EmulatedDevice::getStringDescriptorDataFromString(const std::string to_convert){
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

uint8_t* EmulatedDevice::getStringDescriptorFromId(int id){
	if(id_string_descriptor_mapping_.find(id) != id_string_descriptor_mapping_.end()){
		return getStringDescriptorDataFromString(id_string_descriptor_mapping_.at(id));
	}else{
		throw new std::runtime_error("No matching string found!");
	}
}

const uint8_t* EmulatedDevice::getDeviceDescriptor(){
	return dev_desc;
}

const uint8_t* EmulatedDevice::getConfigurationDescriptor(){
	return conf_desc;
}

const uint8_t* EmulatedDevice::getLanguageDescriptor(){
	return current_language_;
}

uint8_t* EmulatedDevice::getCurrentDataToSendAsUint8Array(){
	std::string current_data_to_send = send_buffer_.str();
	send_buffer_.str(std::string());
	send_buffer_.clear();
	return getStringDescriptorDataFromString(current_data_to_send);
}

void EmulatedDevice::setRecievedData(uint8_t* data, int length){
	uint8_t string_data[length + 1];
	std::copy(data, data + length, string_data);
	string_data[length] = '\0';

	std::string input(reinterpret_cast<char*>(string_data));
//	std::cout << "length = " << length << std::endl;
//	std::cout << "input = " << input << std::endl;
	if(length == 1 && string_data[0] == 0x0d){
		evaluateCommand();
	}else{
		current_incomplete_command_ << input;
	}


}

void EmulatedDevice::evaluateCommand(){
	//just stream into file for communication
	std::string command_got_ = current_incomplete_command_.str();
	std::cout << command_got_ << std::endl;
	int break_position = -1;
	while((break_position = command_got_.find('\r')) != -1){
		command_got_.at(break_position) = ' ';
	}

//	std::cout << "Break position: " << break_position << std::endl;

	if(command_received_callback_ != NULL){
		command_received_callback_(command_got_);
	}else{
		defaultCommandHandler(command_got_);
	}

//	std::cout << "\ncurrent command_: " << std::endl;
//	std::cout << command_got_ << std::endl;
	current_incomplete_command_.str(std::string());
	current_incomplete_command_.clear();
}

void EmulatedDevice::defaultCommandHandler(std::string command){
	addAnswerToQueue("Callback not initialized...");
}

void EmulatedDevice::addAnswerToQueue(std::string data){
	send_buffer_ << data << "\n\r>";
}

std::string EmulatedDevice::getCurrentSendBuffer(){
	return send_buffer_.str();
}
