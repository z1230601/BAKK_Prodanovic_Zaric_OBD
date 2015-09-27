#include "uart.h"

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <iostream>

Uart::Uart(string portName)
{
    _portName = portName;
    _currentBaudRate = Uart::BR115200;
    _device = 0;

}
Uart::~Uart()
{
    if ( _device >= 0)
        close( _device );
}

int Uart::openDevice()
{
    _device = open ( _portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    return _device;
}

void Uart::send(string data)
{
    if ( _device >= 0 )
        write ( _device , data.c_str(), data.size()+1);
}

void Uart::send(int data)
{
    write ( _device , &data, 1);
}

void Uart::closeDevice()
{
    if ( _device >= 0)
        close( _device );
    _device = 0;
}
bool Uart::isDeviceOpen()
{
    return _device >= 0;
}

string Uart::readData()
{
    if ( _device < 0 )
        return "Err.";
    char buf [100] = {0};

    int cmpt_read = 0;
    int current_read = 0;
    std::string line;
    while((current_read = read (_device, buf, 100)) > 0){
    	cmpt_read += current_read;
    	line += std::string(buf);
    	current_read = 0;
    	memset(buf, '\0', 100);
    }
    if ( cmpt_read > 0)
        return line.c_str();
    else
        return "";
}

int Uart::uartBaudRate2int( Uart::baud_rate baudrate)
{
    switch( baudrate )
    {
     case Uart::BR57600 :
        return B57600;
        break;
    case Uart:: BR115200:
        return B115200;
        break;
    case Uart::BR230400 :
        return B230400;
        break;
    case Uart::BR460800 :
        return B460800;
        break;
    case Uart::BR38400:
    	return B38400;
    case Uart::BR500000 :
        return B500000;
        break;
    case Uart::BR576000 :
        return B576000;
        break;
    case Uart::BR921600 :
        return B921600;
        break;
    case Uart::BR1000000 :
        return B1000000;
        break;
    case Uart::BR1152000 :
        return B1152000;
        break;
    case Uart::BR1500000 :
        return B1500000;
        break;
    case Uart::BR2000000 :
        return B2000000;
        break;
    case Uart::BR2500000 :
        return B2500000;
        break;
    case Uart::BR3000000 :
        return B3000000;
        break;
    case Uart::BR3500000 :
        return B3500000;
        break;
    case Uart::BR4000000 :
        return B4000000;
        break;
    default :
        return B115200;
        break;
    }
}

int Uart::setInterfaceAttrib ( Uart::baud_rate speed, int parity )
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (_device, &tty) != 0)
    {
        return -1;
    }

    cfsetospeed ( &tty, uartBaudRate2int(speed) );
    cfsetispeed ( &tty, uartBaudRate2int(speed) );

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // ignore break signal
    tty.c_lflag = 0;                // no signaling chars, no echo,
    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 0;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (_device, TCSANOW, &tty) != 0)
    {
        return -1;
    }
    return 0;
}


void Uart::setBlocking ( int should_block )
{
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (_device, &tty) != 0)
    {
        return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (_device, TCSANOW, &tty) != 0)
        return;
}

