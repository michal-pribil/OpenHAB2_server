#include <map>
#include <RF24/RF24.h>
#include "Timing.h"

// class RF24DeviceEndpoint
// {
  // public:
    // RF24Device();
    // Run();
    // std::array<uint8_t, 16> GetFunctions();
    // virtual Setup
// };

namespace rf24device
{
  static const uint8_t address_ep_global = 0x00;
  
  static const uint8_t cmd_ep_config = 0x10;
  
  typedef struct {
        uint8_t ep;
        uint8_t cmd;
        uint8_t data_length;
        uint8_t data[25];
        uint32_t encrypted_crc;
      } t_message;
}   

class RF24Device 
{
  public:
    RF24Device(uint8_t address, RF24& radio);
    ~RF24Device();
    void Transaction(rf24device::t_message* message, float timeout);
    void Run();
    std::map<uint8_t, RF24Device> ScanForDevices();
  private:
    RF24& mRadio;
    Timing mTiming;
    void GetFunctions();  
};
