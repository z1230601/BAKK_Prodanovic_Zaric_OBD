#include "DeviceDetector.h"
#include <iostream>
#include <stdexcept>

std::vector<Device> DeviceDetector::detectDevices() {

	std::vector<Device> device_list;

	handleError(libusb_init(&context), ErrorHandling::INIT);

	libusb_set_debug(context, 3);

	handleError((device_counter = libusb_get_device_list(context, &devices)),
			ErrorHandling::DEVICELIST);

	std::cout << device_counter << " Devices in list" << std::endl;

	for (int i = 1; i < device_counter; i++) {
		handleError(libusb_get_device_descriptor(devices[i], &desc),
				ErrorHandling::DEVICEDESCRIPTOR);
		handleError(libusb_open(devices[i], &device_handle),
				ErrorHandling::OPENDEVICE);
		handleError(libusb_get_string_descriptor_ascii(device_handle, desc.iManufacturer, (unsigned char*) manufacturer, sizeof(manufacturer)),
				ErrorHandling::MANUFACTURER);
		handleError(libusb_get_string_descriptor_ascii(device_handle, desc.iProduct, (unsigned char*) product, sizeof(product)),
				ErrorHandling::PRODUCT);
		device_list.push_back(Device(manufacturer, product, desc.idProduct, desc.idVendor));
	}

	libusb_free_device_list(devices, 1); //free the list, unref the devices in it
	libusb_exit(context); //close the session
	return device_list;
}

void DeviceDetector::handleError(int errorValue, ErrorHandling what) {
	switch (what) {
	case ErrorHandling::INIT:
		if (errorValue < 0) {
			throw std::runtime_error("Initialization Error");
		}
		break;
	case ErrorHandling::DEVICELIST:
		if (errorValue < 0) {
			throw std::runtime_error("Error getting Devices");
		}
		break;
	case ErrorHandling::DEVICEDESCRIPTOR:
		if (errorValue < 0) {
			throw std::runtime_error("Failed to get Device Descriptor");
		}
		break;
	case ErrorHandling::OPENDEVICE:
		if (errorValue < 0) {
			throw std::runtime_error("Failed to open Device");
		}
		break;
	case ErrorHandling::MANUFACTURER:
	case ErrorHandling::PRODUCT:
		if (errorValue < 0) {
			libusb_close(device_handle);
			throw std::runtime_error("Manufacturer or product not found");
		}
		break;
	}
}
