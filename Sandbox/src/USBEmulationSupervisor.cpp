#include "USBEmulationSupervisor.h"
#include "USBRequestHandler.h"

bool USBEmulation::has_work_;
bool USBEmulation::waiting_for_work_;
boost::mutex USBEmulation::has_work_mutex_;
boost::condition_variable USBEmulation::has_work_cv_;

USBEmulation::USBEmulation() {
	try {
		emulation_interface_ = new usb::vhci::local_hcd(1);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	emulation_interface_->add_work_enqueued_callback(usb::vhci::hcd::callback(&notifyJobQueued, NULL));
}

USBEmulation::~USBEmulation() {
	delete emulation_interface_;
}

void USBEmulation::notifyJobQueued(void* arg,
		usb::vhci::hcd& from) throw () {
	has_work_mutex_.lock();
	has_work_ = true;
	if (waiting_for_work_) {
		waiting_for_work_ = false;
		has_work_cv_.notify_one();
	}
	has_work_mutex_.unlock();
}

void USBEmulation::process_urb(usb::urb* urb) {
	if(urb->is_bulk()){
		USBRequestHandler::getInstance()->handleBulkRequest(urb);
		return;
	}
	if(!urb->is_control())
	{
		std::cout << "not CONTROL" << std::endl;
		return;
	}
	if(urb->get_endpoint_number())
	{
		std::cout << "not ep0" << std::endl;
		urb->stall();
		return;
	}
	USBRequestHandler::getInstance()->handleUSBRequest(urb);
}

void USBEmulation::run() {
	bool continue_work_(false);
	while (true) {
		if (!continue_work_) {
			has_work_mutex_.lock();
			if (!has_work_) {
				waiting_for_work_ = true;
				boost::unique_lock<boost::mutex> lock(has_work_mutex_);
				has_work_cv_.wait(lock);
				//pthread_cond_wait(&has_work_cv, &has_work_mutex);
			} else
				has_work_ = false;
			has_work_mutex_.unlock();
		}
		usb::vhci::work* work;
		continue_work_ = emulation_interface_->next_work(&work);
		if (work) {
			if (usb::vhci::port_stat_work* psw =
					dynamic_cast<usb::vhci::port_stat_work*>(work)) {
				std::cout << "got port stat work" << std::endl;
				std::cout << "status: 0x" << std::setw(4) << std::setfill('0')
						<< std::right << std::hex
						<< psw->get_port_stat().get_status() << std::endl;
				std::cout << "change: 0x" << std::setw(4) << std::setfill('0')
						<< std::right << psw->get_port_stat().get_change()
						<< std::endl;
				std::cout << "flags:  0x" << std::setw(2) << std::setfill('0')
						<< std::right
						<< static_cast<int>(psw->get_port_stat().get_flags())
						<< std::endl;
				if (psw->get_port() != 1) {
					std::cerr << "invalid port" << std::endl;
					return;
				}
				if (psw->triggers_power_off()) {
					std::cout << "port is powered off" << std::endl;
				}
				if (psw->triggers_power_on()) {
					std::cout << "port is powered on -> connecting device"
							<< std::endl;
					emulation_interface_->port_connect(1, usb::data_rate_full);
				}
				if (psw->triggers_reset()) {
					std::cout << "port is resetting" << std::endl;
					if (emulation_interface_->get_port_stat(1).get_connection()) {
						std::cout << "-> completing reset" << std::endl;
						emulation_interface_->port_reset_done(1);
					}
				}
				if (psw->triggers_resuming()) {
					std::cout << "port is resuming" << std::endl;
					if (emulation_interface_->get_port_stat(1).get_connection()) {
						std::cout << "-> completing resume" << std::endl;
						emulation_interface_->port_resumed(1);
					}
				}
				if (psw->triggers_suspend())
					std::cout << "port is suspended" << std::endl;
				if (psw->triggers_disable())
					std::cout << "port is disabled" << std::endl;
			} else if (usb::vhci::process_urb_work* puw =
					dynamic_cast<usb::vhci::process_urb_work*>(work)) {
//				std::cout << "got process urb work" << std::endl;
				process_urb(puw->get_urb());
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
