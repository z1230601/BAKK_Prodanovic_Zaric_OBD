#ifndef EMULATEDDEVICE_H_
#define EMULATEDDEVICE_H_

#include <vector>
#include <sstream>
#include <string.h>
#include <map>
#include <boost/function.hpp>

class EmulatedDevice{

private:
	uint16_t address;
	std::stringstream current_incomplete_command_;
	std::stringstream send_buffer_;
	std::map<int, std::string> id_string_descriptor_mapping_;
	uint8_t* current_language_;
	boost::function<void (std::string)> command_received_callback_;

	uint8_t* getStringDescriptorDataFromString(const std::string to_convert);

	void evaluateCommand();
	void initStringDescriptorMapping();
	void defaultCommandHandler(std::string command);

public:
	EmulatedDevice();

	EmulatedDevice(boost::function<void (std::string)> const &to_set);
	EmulatedDevice(void (*to_set)(std::string &));

	~EmulatedDevice();
	EmulatedDevice(EmulatedDevice & cpy);

	const uint8_t* getDeviceDescriptor();
	const uint8_t* getConfigurationDescriptor();
	const uint8_t* getLanguageDescriptor();

	uint8_t* getStringDescriptorFromId(int id);
	uint8_t* getCurrentDataToSendAsUint8Array();
	void setRecievedData(uint8_t* data, int length);

	void addAnswerToQueue(std::string data);

	//for testing
	std::string getCurrentSendBuffer();


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

std::map<std::string, uint8_t[]> laguanges_{{"ENGLISH",{
	4,      // descriptor length
	3,      // type: string
	0x09,   // lang id: english (us)
	0x04    //  "
}}, {"GERMAN",{
        4,      // descriptor length
        3,      // type: string
        0x07,   // lang id: german  (us)
        0x04    //  "
    }}};

#endif /* EMULATEDDEVICE_H_ */
