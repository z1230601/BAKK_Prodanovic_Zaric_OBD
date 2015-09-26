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

#include "uart.h"
#include "SerialCommunication.h"

int main(int argc, char* argv[]) {
	if(argc != 3){
		std::cout << "Not enough arguments!\n" << std::endl;
		return -1;
	}
	SerialCommunication* comm;

	try{
		comm = new SerialCommunication(argv[1], argv[2]);
	}catch(std::runtime_error e){
		std::cout << "SerialCommunication couldn't be initialized\n";
		return -1;
	}catch(std::exception e){
		std::cout << e.what();
	}

	std::string command;
	while (true) {
		std::cout << "Enter Command: " << std::endl;
		std::getline(std::cin, command);
		std::cout << "Command got: " << command << std::endl;
		if(strcmp(command.c_str(), "exit") == 0){
			break;
		}
		comm->sendCommand(command);
		sleep(0.2);
		std::cout << comm->getResponse() << std::endl;
	}
}
