#include <map>
// #include <RF24/RF24.h>


// class RF24DeviceEndpoint
// {
  // public:
    // RF24Device();
    // Run();
    // std::array<uint8_t, 16> GetFunctions();
    // virtual Setup
// };

#define EP_GLOBAL 0x00

class RF24Device 
{
  public:
    
    typedef struct {
      uint8_t ep;
      uint8_t cmd;
      uint8_t data_length;
      uint8_t data[25];
      uint32_t encrypted_crc;
    } t_message;
    
    RF24Device();
    Transaction(t_message* message, float timeout);
    Run();
    static std::map<uint8_t, RF24Device> ScanForDevices();
  private:
    RF24& mRadio;
    Timing mTiming;
    GetFunctions();  
};
