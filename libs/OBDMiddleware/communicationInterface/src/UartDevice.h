#ifndef UART_DEVICE_H
#define UART_DEVICE_H


#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <stdio.h>

#include <fcntl.h>

typedef std::string string;

class UartDevice
{
public:
    enum baud_rate {
        BR57600, BR115200, BR230400, BR460800,  BR38400, BR500000,  BR576000,  BR921600, BR1000000,
        BR1152000, BR1500000, BR2000000, BR2500000, BR3000000, BR3500000, BR4000000
    };

    UartDevice( string portName );
    ~UartDevice();

    int openDevice();
    void closeDevice();
    bool isDeviceOpen();
    int setInterfaceAttrib (UartDevice::baud_rate speed, int parity );
    void setBlocking ( int should_block );
    int uartBaudRate2int( UartDevice::baud_rate baudrate);

    void send( string data );
    void send(int data);
    string readData( );



private:
    string _portName;
    int _device;
    baud_rate _currentBaudRate;
};

#endif // UART_DEVICE_H

