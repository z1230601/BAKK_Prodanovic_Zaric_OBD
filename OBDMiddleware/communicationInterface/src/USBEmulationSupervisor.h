#ifndef USBEMULATIONSUPERVISOR_H_
#define USBEMULATIONSUPERVISOR_H_

#include <unistd.h>
#include <iostream>
#include <execinfo.h>
#include <iomanip>
#include <libusb_vhci.h>
#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>

class USBRequestHandler;

class USBEmulationSupervisor{
private:
	bool running_ = false;
	usb::vhci::local_hcd* emulation_interface_;
	USBRequestHandler* request_handler_;

	static void notifyJobQueued(void* arg, usb::vhci::hcd& from) throw();
	void process_usb_request_block_(usb::urb* urb);
	void updateWorkState();
	void handleIncomingPortStatusWork(usb::vhci::port_stat_work* port_status_work);

public:
	USBEmulationSupervisor();
	~USBEmulationSupervisor();
	void run();

	bool isRunning();
	void terminate();

	USBRequestHandler* getRequestHandler() const;
};



#endif /* USBEMULATIONSUPERVISOR_H_ */
