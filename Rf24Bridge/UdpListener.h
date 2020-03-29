#include <string>
#include <list>
#include <thread>

class UdpListener
{
public:
  UdpListener();
  ~UdpListener();
  std::string GetNextPacket();
  
private:
  int s;
  bool terminate = 0;
  
  std::list<std::string> bufferedPackets;
  std::thread receiverThread;
  
  void ReceiverThreadWorker();
};