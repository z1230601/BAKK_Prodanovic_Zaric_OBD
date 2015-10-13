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

class USBEmulation{
private:
	usb::vhci::local_hcd* emulation_interface_;
	static boost::mutex has_work_mutex_;
	static boost::condition_variable has_work_cv_;
	static bool has_work_;
	static bool waiting_for_work_;

	static void notifyJobQueued(void* arg, usb::vhci::hcd& from) throw();
	static void process_urb(usb::urb* urb);

public:
	USBEmulation();
	~USBEmulation();
	void run();
};



#endif /* USBEMULATIONSUPERVISOR_H_ */
