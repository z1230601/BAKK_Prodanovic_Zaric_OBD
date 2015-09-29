#include "DeviceDetector.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/filesystem.hpp>

DeviceDetector::DeviceDetector() {
	detectDevices();
}

DeviceDetector::~DeviceDetector() {
}

std::vector<Device> DeviceDetector::detectDevices() {
	libusb_device **devices;
	libusb_context *context = NULL;
	int device_counter = 0;

	handleError(libusb_init(&context), ErrorHandling::INIT);

	libusb_set_debug(context, 3);

	handleError((device_counter = libusb_get_device_list(context, &devices)),
			ErrorHandling::DEVICELIST);

	for (int i = 0; i < device_counter; i++) {
			device_list.push_back(getDeviceIfPossible(devices[i]));
			std::cout << device_list.at(i);
	}

	libusb_free_device_list(devices, 1); //free the list, unref the devices in it
	libusb_exit(context); //close the session
	return device_list;
}

Device DeviceDetector::getDeviceIfPossible(libusb_device* dev){
	libusb_device_handle *device_handle;
	libusb_device_descriptor desc;
	char manufacturer[256], product[256];
	handleError(libusb_get_device_descriptor(dev, &desc),
			ErrorHandling::DEVICEDESCRIPTOR);
	handleError(libusb_open(dev, &device_handle),
			ErrorHandling::OPENDEVICE);
	try {
		handleError(
				libusb_get_string_descriptor_ascii(device_handle,
						desc.iManufacturer, (unsigned char*) manufacturer,
						sizeof(manufacturer)), ErrorHandling::MANUFACTURER);
	} catch (std::runtime_error &err) {
		manufacturer[0] = '\0';
	}

	try {
		handleError(
				libusb_get_string_descriptor_ascii(device_handle, desc.iProduct,
						(unsigned char*) product, sizeof(product)),
				ErrorHandling::PRODUCT);
	} catch (std::runtime_error &err) {
		product[0] = '\0';
	}

	unsigned int bus = libusb_get_bus_number(dev);
	unsigned int port = libusb_get_port_number(dev);

	std::string path = getTTYPath(bus, port);

	std::cout << path << std::endl;

	libusb_close(device_handle);
	return Device(manufacturer, product, desc.idProduct, desc.idVendor, bus, port, path);
}

std::string DeviceDetector::getTTYPath(unsigned int bus, unsigned int port) {
	std::string path = "";
	std::string deviceID = std::to_string(bus) + "-" + std::to_string(port);
	if(bus == 0 || port == 0)
		return path;

	path = "/sys/bus/usb/devices/";
	path +=  deviceID + "/";

	boost::filesystem::path system_path(path);

	if(boost::filesystem::exists(system_path) && boost::filesystem::is_directory(system_path)) {

		std::cout << system_path << " is a directory containing:" << std::endl;

		typedef std::vector<boost::filesystem::path> vec;		// store paths,
		vec v;                                					// so we can sort them later

		std::copy(boost::filesystem::directory_iterator(system_path),
				boost::filesystem::directory_iterator(), std::back_inserter(v));
		sort(v.begin(), v.end());						// sort, since directory iteration
														// is not ordered on some file systems
		for (vec::const_iterator it (v.begin()); it != v.end(); ++it) {
			std::cout << "   " << *it << std::endl;
		}
	}

	return path;
}

void DeviceDetector::handleError(int errorValue, ErrorHandling what) {
	std::string message = "";
	if (errorValue < 0) {
		message = error_messages_.at(what);
	}
	if(!message.empty()){
		throw std::runtime_error(message);
	}
}
