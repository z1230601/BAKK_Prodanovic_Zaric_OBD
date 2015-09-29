#ifndef DEVICEDETECTOR_H_
#define DEVICEDETECTOR_H_

#include "Device.h"
#include <vector>
#include <libusb-1.0/libusb.h>
#include <boost/filesystem.hpp>
#include <map>

typedef boost::filesystem::path path;

enum ErrorHandling {
	INIT, DEVICELIST, DEVICEDESCRIPTOR, OPENDEVICE, MANUFACTURER, PRODUCT
};

class DeviceDetector {
public:
	DeviceDetector();
	~DeviceDetector();
	std::vector<Device> detectDevices();
	unsigned int getDeviceListSize() const { return device_list.size(); }
	std::string getTTYPath(unsigned int bus, std::vector<int> port);
	std::vector<int> getPortsFromSystem(libusb_device* dev);

	std::vector<Device> getDeviceList() const {
		return device_list;
	}

	void setDeviceList(std::vector<Device> deviceList) {
		device_list = deviceList;
	}

private:
	std::vector<Device> device_list;

	void handleError(int errorValue, ErrorHandling what);
	Device getDeviceIfPossible(libusb_device* dev);
	path getPathBeginningWith(path search_path, std::string beginning_sequence);
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
