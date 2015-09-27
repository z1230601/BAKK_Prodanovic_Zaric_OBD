/*
 * Main.cpp
 *
 *  Created on: Sep 8, 2015
 *      Author: zlatan
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <termios.h>
#include <errno.h>
#include <pthread.h>
#include <stdexcept>

#include "SerialCommunication.h"
#include "DeviceDetector.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cout << "Not enough arguments!\n" << std::endl;
		return -1;
	}
	SerialCommunication* comm;

	try {
		comm = new SerialCommunication(argv[1], argv[2]);
	} catch (std::runtime_error e) {
		std::cout << "SerialCommunication couldn't be initialized\n";
		return -1;
	} catch (std::exception e) {
		std::cout << e.what();
	}

	std::string command;
	while (true) {
		std::cout << "Enter Command: " << std::endl;
		std::getline(std::cin, command);
		std::cout << "Command got: " << command << std::endl;
		if (strcmp(command.c_str(), "exit") == 0) {
			break;
		} else if (strcmp(command.c_str(), "detect") == 0) {
			DeviceDetector* deviceList;
			try{
				deviceList = new DeviceDetector();
				std::cout << "Found Devices: " << deviceList->getDeviceListSize() << std::endl;
			}catch(std::runtime_error &err){
				std::cout << "caught exception with: " << err.what() << std::endl;
			}catch(std::exception &e){
				std::cout << "caught generell execption: " << e.what() << std::endl;
			}
		} else {
			comm->sendCommand(command);
			while (!comm->isResponseReady()) {
				sleep(0.2);
			}

			std::pair<std::string, std::string> response =
					comm->getTopResponse();
			std::cout << response.first << "->" << response.second << std::endl;
		}
	}
}
