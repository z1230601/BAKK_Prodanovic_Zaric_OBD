/*
 * SerialCommunication.h
 *
 *  Created on: Sep 20, 2015
 *      Author: zlatan
 */

#include "uart.h"
#include <list>
#include <sstream>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <utility>

#ifndef SERIALCOMMUNICATION_H_
#define SERIALCOMMUNICATION_H_

#define INTERPRETATION_PERIOD_IN_TICKS 1000000

class SerialCommunication{
public:
	SerialCommunication(std::string dev, std::string baudrate);
	~SerialCommunication();

	void sendCommand(std::string &command);
	std::pair<std::string, std::string> getTopResponse();
	bool isResponseReady();

private:
	Uart* serial_device_;
	boost::mutex device_lock_;

	std::list<std::pair<std::string,std::string>> response_queue_;
	boost::mutex response_queue_lock_;

	std::stringstream reading_stream_;
	boost::mutex reading_stream_lock_;

	boost::thread reading_thread_;

	SerialCommunication(SerialCommunication& cpy);
	SerialCommunication();

	void startReadingThread();
	void readInputStream();
	void interpretResponses();

};

#endif /* SERIALCOMMUNICATION_H_ */
