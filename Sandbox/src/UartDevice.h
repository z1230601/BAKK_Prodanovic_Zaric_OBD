#ifndef UART_DEVICE_H
#define UART_DEVICE_H


#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <map>

typedef std::string string;

class UartDevice
{
public:
	int getBaudRateFromString(string baudrate);

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

	std::map<int, int> validBaudrates{
		{38400,B38400},
		{57600,B57600},
		{115200,B115200},
		{230400,B230400},
		{460800,B460800},
		{500000,B500000},
		{500000,B500000},
		{921600,B921600},
		{1000000,B1000000},
		{1152000,B1152000},
		{1500000,B1500000},
		{2000000,B2000000},
		{2500000,B2500000},
		{3000000,B3000000},
		{3500000,B3500000},
		{4000000,B4000000}
	};
};

#endif // UART_DEVICE_H

