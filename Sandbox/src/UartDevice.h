#ifndef UART_DEVICE_H
#define UART_DEVICE_H


#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <algorithm>

typedef std::string string;

class UartDevice
{
public:
	std::vector<int> validBaudrates {B38400,B57600,B115200,B230400,B460800,
		B500000, B576000,B921600,B1000000,B1152000,B1500000,B2000000,B2500000,B3000000, B3500000, B4000000}

	static int getBaudRateFromString(string baudrate){
    	int baud_rate = std::stoi(baudrate);
    	if(std::find(validBaudrates.begin(), validBaudrates.end(), baud_rate) != validBaudrates.end()) {
    	    return baud_rate;
    	} else {
    		return B38400;
    	}
    }

    UartDevice( string portName );
    ~UartDevice();

    int openDevice();
    void closeDevice();
    bool isDeviceOpen();
    int setInterfaceAttrib (int speed, int parity );
    void setBlocking ( int should_block );

    void send( string data );
    void send(int data);
    string readData( );



private:
    string _portName;
    int _device;
    int _currentBaudRate;
};

#endif // UART_DEVICE_H

