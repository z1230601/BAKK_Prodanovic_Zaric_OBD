#ifndef DEVICEDETECTOR_H_
#define DEVICEDETECTOR_H_

#include <libusb-1.0/libusb.h>

enum ErrorHandling {
	INIT, DEVICELIST, DEVICEDESCRIPTOR, OPENDEVICE, MANUFACTURER, PRODUCT
};

class DeviceDetector {
public:
	std::vector<Device> detectDevices();

private:
	libusb_device **devices;
	libusb_device_handle *device_handle;
	libusb_context *context = NULL;
	libusb_device_descriptor desc;
	int device_counter = 0;
	char manufacturer[256], product[256];

	void handleError(int errorValue, ErrorHandling what);
};

#endif /* DEVICEDETECTOR_H_ */
