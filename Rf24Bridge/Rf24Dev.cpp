RF24Device::RF24Device(uint8_t address, RF24& radio)
 : mRadio(radio)
{
}

Transaction(t_message* message, float timeout)
{
  if (!radio.writeFast(static_cast<uint8_t*>(message), 32)) {     //Write to the FIFO buffers
    counter++;                      //Keep count of failed payloads
  }
}

RF24Device::Run()
{
}

static std::map<uint8_t, RF24Device> ScanForDevices(RF24& radio)
{
  
}

GetFunctions()
{
  
}
    
    
