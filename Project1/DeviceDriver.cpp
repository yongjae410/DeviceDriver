#include "DeviceDriver.h"
#include <Windows.h>
#include <stdexcept>

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
            throw std::invalid_argument("Read failed");
	    }
    }
    return val;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}