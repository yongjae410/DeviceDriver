#include "DeviceDriver.h"
#include <Windows.h>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int val = (int)(m_hardware->read(address));
    for(int tries = 1; tries < 5; tries++)
    {
        Sleep(200);
	    if (val != (int)(m_hardware->read(address)))
	    {
            throw ReadFailException();
	    }
    }
    return val;
}

void DeviceDriver::write(long address, int data)
{
    if (0xFF != (int)(m_hardware->read(address)))
    {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);
}