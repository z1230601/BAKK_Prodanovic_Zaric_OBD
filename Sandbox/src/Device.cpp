#include "Device.h"

Device::Device(std::string manufacturer, std::string product,
		unsigned int productID, unsigned int vendorID) {
	setManufacturer(manufacturer);
	setProdcut(product);
	setProductId(productID);
	setVendorId(vendorID);
}

Device::~Device() {

}

