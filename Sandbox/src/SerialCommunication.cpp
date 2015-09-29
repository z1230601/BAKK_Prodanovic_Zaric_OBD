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
	serial_device_ = new UartDevice(devicePath);
	serial_device_ ->openDevice();
	serial_device_ -> setInterfaceAttrib(serial_device_->getBaudRateFromString(baudrate), 1);
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
		std::string output = "";
		if(serial_device_->isDeviceOpen()){
			boost::lock_guard<boost::mutex> lock(device_lock_);
			output = serial_device_->readData();
		}

		if(!output.empty()){
			boost::lock_guard<boost::mutex> lock(reading_stream_lock_);
			reading_stream_ << output ;
			if (output.find(">") != std::string::npos) {
				interpretResponses();
			}
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
	std::string read_data;
	std::string first;
	while (first != ">") {
		std::getline(reading_stream_, read_data, '\n');
		if (read_data.empty() || read_data == "\n") {
			continue;
		}
		if (first.empty()) {
			first = read_data;
			std::cout << "first: " << first << std::endl;
		} else {
			boost::lock_guard<boost::mutex> lock(response_queue_lock_);
			response_queue_.push_back(std::make_pair(first, read_data));
			first = "";
		}
		read_data = "";
	}
	reading_stream_.str(std::string());
	reading_stream_.clear();
}
