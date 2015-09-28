#include "Device.h"

Device::Device(std::string manufacturer, std::string product,
		unsigned int productID, unsigned int vendorID, unsigned int busnumber,
		unsigned int portnumber, std::string ttypath) {
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

