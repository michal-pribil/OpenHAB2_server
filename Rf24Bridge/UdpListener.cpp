/*
	Simple udp server
*/
#include <stdio.h>	//printf
#include <string.h> //memset
#include <string>
#include <functional>
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "UdpListener.h"
#include <chrono>

#define BUFLEN 512	//Max length of buffer
#define PORT 8150	//The port on which to listen for incoming data

using namespace std;
using namespace std::chrono_literals;

UdpListener::UdpListener(void)
{
  struct sockaddr_in si_me;
  printf("*************************************************************************************\n");
  //create a UDP socket
  if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
  {
   // die(string("socket").c_str());
  }
  
  // zero out the structure
  memset((char *) &si_me, 0, sizeof(si_me));
  
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(PORT);
  si_me.sin_addr.s_addr = htonl(INADDR_ANY);
  
  //bind socket to port
  if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
  {
    // die(string("bind").c_str());
  }
  
  receiverThread = std::thread(std::bind(&UdpListener::ReceiverThreadWorker, this));
}

UdpListener::~UdpListener()
{
  close(s);
  terminate = 1;
  receiverThread.join();
}

std::string UdpListener::GetNextPacket()
{
  string retVal;
  if (bufferedPackets.size() > 0)
  {
	retVal = bufferedPackets.front();
	bufferedPackets.pop_front();
	return retVal;
  }
  else 
  {
	return "";
  }
}
  
void UdpListener::ReceiverThreadWorker()
{
  char buf[BUFLEN];
  struct sockaddr_in si_other;
  unsigned int slen = sizeof(si_other);
  int recv_len;

  while(1)
  {
    printf("Waiting for data...");
    fflush(stdout);
    
     //try to receive some data, this is a blocking call
    if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
    {
	  if (terminate)
	    return;
    // die(string("recvfrom()").c_str());
    }
    else
	{
      //print details of the client/peer and the data received
      printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
      printf("Data: %s\n", buf);
	  bufferedPackets.push_back(string(buf));
	}
	
	// std::this_thread::sleep_for(1s);
    
  //now reply the client with the same data
  //if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
  //{
  //	die(string("sendto()").c_str());
  //}
  }
}

// void die(const char *s)
// {
	// perror(s);
	// exit(1);
// }

// int main (int argc, char** argv)
// {
	// return 0;
// }