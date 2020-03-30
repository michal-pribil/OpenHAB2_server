#include "Rf24Dev.h"

RF24Device::RF24Device(uint8_t address, RF24& radio)
 : mRadio(radio)
{
}

RF24Device::~RF24Device(){};

void RF24Device::Transaction(rf24device::t_message* message, float timeout)
{
  if (!mRadio.writeFast(reinterpret_cast<uint8_t*>(message), 32)) {     //Write to the FIFO buffers
    // counter++;                      //Keep count of failed payloads
  }
}

void RF24Device::Run()
{
}

std::map<uint8_t, RF24Device> RF24Device::ScanForDevices()
{
  
}

void RF24Device::GetFunctions()
{
  
}