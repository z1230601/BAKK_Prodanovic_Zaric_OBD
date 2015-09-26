/*
 * SerialCommunication.h
 *
 *  Created on: Sep 20, 2015
 *      Author: zlatan
 */

#include "uart.h"
#include <vector>
#include <sstream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#ifndef SERIALCOMMUNICATION_H_
#define SERIALCOMMUNICATION_H_


class SerialCommunication{
public:
	SerialCommunication(std::string dev, std::string baudrate);
	~SerialCommunication();

	void sendCommand(std::string &command);
	std::string getResponse();

private:
	Uart* serial_device_;
	boost::mutex device_lock_;

	std::vector<std::string> command_queue_;
	std::stringstream reading_stream_;
	boost::mutex reading_stream_lock_;

	boost::thread reading_thread_;

	SerialCommunication(SerialCommunication& cpy);
	SerialCommunication();

	void startReadingThread();
	void readInputStream();

};

#endif /* SERIALCOMMUNICATION_H_ */
