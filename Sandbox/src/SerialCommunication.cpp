/*
 * SerialCommunication.cpp
 *
 *  Created on: Sep 20, 2015
 *      Author: zlatan
 */

#include "SerialCommunication.h"
#include <iostream>
#include <boost/thread/lock_guard.hpp>

SerialCommunication::SerialCommunication(std::string devicePath, std::string baudrate){
	serial_device_ = new Uart(devicePath);
	serial_device_ ->openDevice();
	serial_device_ -> setInterfaceAttrib(Uart::BR38400, 1);
	startReadingThread();
}

SerialCommunication::~SerialCommunication(){
	delete serial_device_;
	reading_thread_.interrupt();
	reading_thread_.join();
}

void SerialCommunication::startReadingThread(){
	// starting thread using boost library
	try {
		 reading_thread_ = boost::thread(&SerialCommunication::readInputStream, this);
	} catch (boost::thread_interrupted& interruption) {
		// thread was interrupted, this is expected.
	} catch (std::exception& e) {

	}
}

void SerialCommunication::readInputStream(){
	unsigned int tick = 0;
	while(true){
		device_lock_.lock();
		std::string output = serial_device_->readData();
		device_lock_.unlock();

		if(!output.empty()){
			reading_stream_lock_.lock();
			reading_stream_ << output ;
			reading_stream_lock_.unlock();
		}

		if(tick % INTERPRETATION_PERIOD_IN_TICKS == 0){
//			interpretResponses();
			reading_stream_lock_.lock();
			std::cout << reading_stream_.str() << std::endl;
			reading_stream_lock_.unlock();
		}

		tick++;
		sched_yield();
	}
}

void SerialCommunication::sendCommand(std::string& command){
	device_lock_.lock();
	serial_device_->send(command + "\r\n");
	device_lock_.unlock();
}

std::pair<std::string, std::string> SerialCommunication::getTopResponse(){
	boost::lock_guard<boost::mutex> lock(response_queue_lock_);
	if(response_queue_.empty()){
		throw std::runtime_error("Response Queue Empty!");
	}

	std::pair<std::string, std::string> res =response_queue_.front();
	response_queue_.pop_front();
	return res;
}

bool SerialCommunication::isResponseReady(){
	boost::lock_guard<boost::mutex> lock(response_queue_lock_);
	return !response_queue_.empty();
}

void SerialCommunication::interpretResponses() {
	boost::lock_guard<boost::mutex> lock(reading_stream_lock_);
	if(reading_stream_.str().empty())
		return;

	std::cout << "Reading stream is: \n" << reading_stream_.str()
			<< "END" << std::endl;
//	std::stringstream reading_stream_working_cpy(reading_stream_.str());
//	std::string read_data;
//	std::string first;
//	std::string second;
//	bool response_queue_altered = false;
//	bool last_run_completed_pair = false;
//	while (!reading_stream_working_cpy.eof()) {
//		std::getline(reading_stream_working_cpy, read_data, '\n');
//		if(read_data == "\n" && last_run_completed_pair){
//			std::cout << "pair: "<<first << "   " << second << std::endl;
//			response_queue_.push_back(std::make_pair(first, second));
//			last_run_completed_pair = false;
//		}
//		if (read_data.empty() || read_data == "\n") {
//			continue;
//		}
//		if (first.empty()) {
//			first = read_data;
//			std::cout << "first: " << first << std::endl;
//		} else {
//			boost::lock_guard<boost::mutex> lock(response_queue_lock_);
//			second = read_data;
//			first = "";
//			response_queue_altered = true;
//			last_run_completed_pair = true;
//
//		}
//		read_data = "";
//	}
//
//	if (response_queue_altered) {
//		reading_stream_.str( std::string() );
//		if(!first.empty())
//			reading_stream_ << first;
//	}

}
