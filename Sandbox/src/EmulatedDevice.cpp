/*
 * EmulatedDevice.cpp
 *
 *  Created on: Oct 5, 2015
 *      Author: zlatan
 */

#include <cstdlib>
#include "EmulatedDevice.h"

EmulatedDevice::EmulatedDevice(){
	id_string_descriptor_mapping_.insert(std::make_pair(1,"FTDI"));
	id_string_descriptor_mapping_.insert(std::make_pair(2,"FT232R USB UART"));
	id_string_descriptor_mapping_.insert(std::make_pair(3, "A7030PE3"));
	id_string_descriptor_mapping_.insert(std::make_pair(6, "FTDI"));
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
	return selectable_languages;
}
