/*
 * USBEmulationConstants.h
 *
 *  Created on: Oct 4, 2015
 *      Author: zlatan
 */

#ifndef USBEMULATIONCONSTANTS_H_
#define USBEMULATIONCONSTANTS_H_
#include <map>

const std::map<int, std::string> what{
	{0,"URB_RQ_GET_STATUS"},
	{1,"URB_RQ_CLEAR_FEATURE"},
	{3,"URB_RQ_SET_FEATURE"},
	{5,"URB_RQ_SET_ADDRESS"},
	{6,"URB_RQ_GET_DESCRIPTOR"},
	{7,"URB_RQ_SET_DESCRIPTOR"},
	{8,"URB_RQ_GET_CONFIGURATION"},
	{9," URB_RQ_SET_CONFIGURATION"},
	{10,"URB_RQ_GET_INTERFACE"},
	{11,"URB_RQ_SET_INTERFACE"},
	{12,"URB_RQ_SYNCH_FRAME"}
};


const uint8_t dev_desc[] = {
	18,     // descriptor length
	1,      // type: device descriptor
	0x00,   // bcd usb release number
	0x02,   //  "
	0,      // device class: per interface
	0,      // device sub class
	0,      // device protocol
	8,     // max packet size
	0x03,   // vendor id
	0x04,   //  "
	0x01,   // product id
	0x60,   //  "
	0x00,   // bcd device release number
	0x06,   //  "
	1,      // manufacturer string
	2,      // product string
	3,      // serial number string
	1       // number of configurations
};

const uint8_t conf_desc[] = {
	9,      // descriptor length
	2,      // type: configuration descriptor
	32,     // total descriptor length (configuration+interface)
	0,      //  "
	1,      // number of interfaces
	1,      // configuration index
	0,      // configuration string
	0xa0,   // attributes: none
	45,      // max power

	9,      // descriptor length
	4,      // type: interface
	0,      // interface number
	0,      // alternate setting
	2,      // number of endpoints
	0xFF,      // interface class
	0xFF,      // interface sub class
	0xFF,      // interface protocol
	2,       // interface string
	// endpoint 1 in
	7,      //bLength
	5,      //desriptor type
	0x81,    //ep in
	2,         // attributes
	0x40,    //maxpacketsize
	0x00,    //"
	0,      // intervall
	//endpoint 2 out
	7,      //bLength
	5,      //desriptor type
	0x2,    //ep in
	2,         // attributes
	0x40,    //maxpacketsize
	0x00,    //"
	0      // intervall
};


const uint8_t selectable_languages[] = {
	4,      // descriptor length
	3,      // type: string
	0x07,   // lang id: english (us)
	0x04    //  "
};

const std::string string_id1 = "FTDI";
const std::string string_id2 = "FT232R USB UART";
const std::string string_id3 = "A7030PE3";

#endif /* USBEMULATIONCONSTANTS_H_ */
