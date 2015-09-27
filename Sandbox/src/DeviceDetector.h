#ifndef DEVICEDETECTOR_H_
#define DEVICEDETECTOR_H_

#include "Device.h"
#include <vector>
#include <libusb-1.0/libusb.h>
#include <map>

enum ErrorHandling {
	INIT, DEVICELIST, DEVICEDESCRIPTOR, OPENDEVICE, MANUFACTURER, PRODUCT
};

class DeviceDetector {
public:
	DeviceDetector();
	~DeviceDetector();
	std::vector<Device> detectDevices();
	unsigned int getDeviceListSize() const { return device_list.size(); }

private:
	std::vector<Device> device_list;

	void handleError(int errorValue, ErrorHandling what);
	Device getDeviceIfPossible(libusb_device* dev);

	std::map<ErrorHandling, std::string> error_messages_
	{
		std::make_pair (ErrorHandling::INIT, "Initialization Error"),
		std::make_pair (ErrorHandling::DEVICELIST, "Error getting Devices"),
		std::make_pair (ErrorHandling::DEVICEDESCRIPTOR, "Failed to get Device Descriptor"),
		std::make_pair (ErrorHandling::OPENDEVICE, "Failed to open Device"),
		std::make_pair (ErrorHandling::MANUFACTURER, "Manufacturer not found"),
		std::make_pair (ErrorHandling::PRODUCT, "Product not found")
	};
};

#endif /* DEVICEDETECTOR_H_ */
