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
#include "uart.h"

int main(int argc, char* argv[]) {

	Uart* uart = new Uart(std::string(argv[1]));
	uart->openDevice();
	uart->setInterfaceAttrib(Uart::BR38400, 1);

	std::string command;
	while (true) {
		std::cout << "Enter Command: " << std::endl;
		std::getline(std::cin, command);
		std::cout << "Command got: " << command << std::endl;
//		std::cout << (int) command.at(command.length()-1);
		if(strcmp(command.c_str(), "exit") == 0){
			break;
		}
		uart->send(command + "\r\n");
		sleep(1);
		std::cout << "recieveing" << std::endl;
		std::string output;
		int i = 0;
		while((output = uart->readData()) != ""){
			std::cout << "i: " << i <<std::endl << output << std::endl;
			i++;
		}

	}
	delete uart;
}

//int main(int argc, char* argv[]) {
//
//	if (argc < 3) {
//		std::cout << "Wrong argument count!" << std::endl;
//		return -1;
//	}
//
//	char* devicename = argv[1];
//	int file = open(devicename, O_RDWR | O_NONBLOCK | O_NOCTTY);
//	int flags = fcntl(file, F_GETFL, 0);
//
//	if (fcntl(file, F_SETFL, flags | O_NONBLOCK)) {
//		std::cout << "read non blocking" << std::endl;
//	}
//
//	if (file < 0) {
//		std::cout << "Error in creating fd.\n";
//	}
//	struct termios oldattr;
//	tcgetattr(file, &oldattr);
//	struct termios attr;
//
//	attr.c_cflag = B38400 | CRTSCTS | CS8 | CLOCAL | CREAD;
//	attr.c_iflag = IGNPAR;
//	attr.c_oflag = 0;
//	attr.c_lflag = 0; //ICANON;
//	attr.c_cc[VMIN] = 1;
//	attr.c_cc[VTIME] = 0;
////	cfsetospeed(&attr, B38400);
////	cfsetispeed(&attr, B38400);
//
//	if (tcflush(file, TCIFLUSH) < 0 || tcflush(file, TCOFLUSH) < 0
//			|| tcsetattr(file, TCSANOW, &attr) < 0) {
//		std::cout << "error at setting baud" << std::endl;
//		return -1;
//	}
//
//	while (true) {
//		std::cout << "sending at i" << std::endl;
//		if (write(file, "at i", 4) < 0) {
//			std::cout << "error while writing" << std::endl;
//		}
//		std::cout << "receiving response" << std::endl;
//		char buff[256];
//		int count = 0;
//
////	if((count=read(file, buff, 256)) < 0 ){
////		std::cout<< "error " << errno << " " << count << std::endl;
////	}
//
//		memset(buff, '\0', 256);
//
//		while ((count = read(file, buff, 256)) < 0 && errno == EAGAIN) {
//			std::cout << "sleeping" << std::endl;
//			sleep(3);
//		}
//
//		do {
//			std::cout << "count: " << count << " buffer : " << std::endl;
//			for (int i = 0; i < 256; i++) {
//				printf("%x ", buff[i]);
//			}
//			std::cout << std::endl;
//		} while ((count = read(file, buff, 256)) >= 0);
//	}
//	close(file);
//}

