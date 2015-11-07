#include "USBEmulationSupervisor.h"
#include "USBRequestHandler.h"

#include <pthread.h>

bool work_is_queued_(true), waiting_for_work(false);
pthread_mutex_t work_is_queued_mutex_;
pthread_cond_t work_present_;

USBEmulationSupervisor::USBEmulationSupervisor() {
	try {
		emulation_interface_ = new usb::vhci::local_hcd(1);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	emulation_interface_->add_work_enqueued_callback(
			usb::vhci::hcd::callback(&notifyJobQueued, NULL));
}

USBEmulationSupervisor::~USBEmulationSupervisor() {
	delete emulation_interface_;
	pthread_mutex_destroy (&work_is_queued_mutex_);
	pthread_cond_destroy (&work_present_);
}

void USBEmulationSupervisor::notifyJobQueued(void* arg, usb::vhci::hcd& from) throw () {
		pthread_mutex_lock(&work_is_queued_mutex_);
		work_is_queued_ = true;

		if(waiting_for_work)
		{
			waiting_for_work = false;
			pthread_cond_signal(&work_present_);
		}

		pthread_mutex_unlock(&work_is_queued_mutex_);
}

void USBEmulationSupervisor::process_usb_request_block_(usb::urb* urb) {
	if (urb->is_bulk()) {
		USBRequestHandler::getInstance()->handleBulkRequest(urb);
		return;
	}
	if (!urb->is_control()) {
		std::cout << "not CONTROL" << std::endl;
		return;
	}
	if (urb->get_endpoint_number()) {
		std::cout << "not ep0" << std::endl;
		urb->stall();
		return;
	}
	USBRequestHandler::getInstance()->handleUSBRequest(urb);
}

void USBEmulationSupervisor::run() {
	bool continue_work_(false);
	while (true) {
		if (!continue_work_) {
			updateWorkState();
		}

		usb::vhci::work* work;
		continue_work_ = emulation_interface_->next_work(&work);
		if (work) {
			if (usb::vhci::port_stat_work* psw =
					dynamic_cast<usb::vhci::port_stat_work*>(work)) {
				handleIncomingPortStatusWork(psw);
			} else if (usb::vhci::process_urb_work* puw =
					dynamic_cast<usb::vhci::process_urb_work*>(work)) {
				process_usb_request_block_(puw->get_urb());
			} else if (dynamic_cast<usb::vhci::cancel_urb_work*>(work)) //usb::vhci::cancel_urb_work* cuw = dynamic_cast<usb::vhci::cancel_urb_work*>(work))
			{
				std::cout << "got cancel urb work" << std::endl;
			} else {
				std::cerr << "got invalid work" << std::endl;
				return;
			}
			emulation_interface_->finish_work(work);
		}
	}
}

void USBEmulationSupervisor::updateWorkState() {
	pthread_mutex_lock(&work_is_queued_mutex_);
	if (!work_is_queued_) {
		waiting_for_work = true;
		pthread_cond_wait(&work_present_, &work_is_queued_mutex_);
	} else
		work_is_queued_ = false;
	pthread_mutex_unlock(&work_is_queued_mutex_);
}

void USBEmulationSupervisor::handleIncomingPortStatusWork(usb::vhci::port_stat_work* port_status_work){
	std::cout << "got port stat work" << std::endl;
	std::cout << "status: 0x" << std::setw(4) << std::setfill('0') << std::right
			<< std::hex << port_status_work->get_port_stat().get_status() << std::endl;
	std::cout << "change: 0x" << std::setw(4) << std::setfill('0') << std::right
			<< port_status_work->get_port_stat().get_change() << std::endl;
	std::cout << "flags:  0x" << std::setw(2) << std::setfill('0') << std::right
			<< static_cast<int>(port_status_work->get_port_stat().get_flags()) << std::endl;
	if (port_status_work->get_port() != 1) {
		std::cerr << "invalid port" << std::endl;
		return;
	}
	if (port_status_work->triggers_power_off()) {
		std::cout << "port is powered off" << std::endl;
	}
	if (port_status_work->triggers_power_on()) {
		std::cout << "port is powered on -> connecting device" << std::endl;
		emulation_interface_->port_connect(1, usb::data_rate_full);
	}
	if (port_status_work->triggers_reset()) {
		std::cout << "port is resetting" << std::endl;
		if (emulation_interface_->get_port_stat(1).get_connection()) {
			std::cout << "-> completing reset" << std::endl;
			emulation_interface_->port_reset_done(1);
		}
	}
	if (port_status_work->triggers_resuming()) {
		std::cout << "port is resuming" << std::endl;
		if (emulation_interface_->get_port_stat(1).get_connection()) {
			std::cout << "-> completing resume" << std::endl;
			emulation_interface_->port_resumed(1);
		}
	}
	if (port_status_work->triggers_suspend())
		std::cout << "port is suspended" << std::endl;
	if (port_status_work->triggers_disable())
		std::cout << "port is disabled" << std::endl;
}
