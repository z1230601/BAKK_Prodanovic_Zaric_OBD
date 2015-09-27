#include "DeviceDetector.h"
#include <iostream>
#include <stdexcept>

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
	libusb_close(device_handle);
	return Device(manufacturer, product, desc.idProduct, desc.idVendor);
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
