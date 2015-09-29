#include "Device.h"

Device::Device(std::string manufacturer, std::string product,
		unsigned int productID, unsigned int vendorID, unsigned int busnumber,
		std::vector<int> portnumber, std::string ttypath) {
	setManufacturer(manufacturer);
	setProdcut(product);
	setProductId(productID);
	setVendorId(vendorID);
	setBusNumber(busnumber);
	setPortNumber(portnumber);
	setSerialDevicePath(ttypath);
}

Device::~Device() {

}

std::string Device::getPortNumberAsString() const{
	std::string port_as_string = "";
	for(unsigned int i = 0; i < port_number_.size(); i++){
		port_as_string += std::to_string(port_number_.at(i)) + ".";
	}
	port_as_string = port_as_string.substr(0, port_as_string.length()-1);
	std::cout << "Port is: " << port_as_string << std::endl;
	return port_as_string;
}
