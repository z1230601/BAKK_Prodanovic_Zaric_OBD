/*
 * SerialCommunication.cpp
 *
 *  Created on: Sep 20, 2015
 *      Author: zlatan
 */

#include "SerialCommunication.h"
#include <iostream>

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
	// starting thread using lambda function
//	std::thread t1([&]{ this->readInputStream(); });
//	pthread_create(&readingThread, NULL,(void*) [&]{ this->readInputStream(); }, NULL);
	try {
		 reading_thread_ = boost::thread(&SerialCommunication::readInputStream, this);
	} catch (boost::thread_interrupted& interruption) {
		// thread was interrupted, this is expected.

	} catch (std::exception& e) {
		// an unhandled exception reached this point, this constitutes an error

	}
}

void SerialCommunication::readInputStream(){
	while(true){
		device_lock_.lock();
		std::string output = serial_device_->readData();
		device_lock_.unlock();

		if(!output.empty()){
			reading_stream_lock_.lock();
			reading_stream_ << output ;
			reading_stream_lock_.unlock();
		}
		sched_yield();
	}
}

void SerialCommunication::sendCommand(std::string& command){
	device_lock_.lock();
	serial_device_->send(command + "\r\n");
	device_lock_.unlock();
}

std::string SerialCommunication::getResponse(){
	std::string response;
	reading_stream_lock_.lock();
	std::cout << reading_stream_.str();
	reading_stream_lock_.unlock();
	return response;
}
