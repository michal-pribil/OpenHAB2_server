#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>
#include <unistd.h>
#include "UdpListener.h"
// #include "Rf24Bridge.h"

using namespace std;

// Setup for GPIO 25 CE and CE0 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_22, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);
UdpListener udpListener;

/****************** Linux (BBB,x86,etc) ***********************/

// See http://tmrh20.github.io/RF24/pages.html for more information on usage
// See http://iotdk.intel.com/docs/master/mraa/ for more information on MRAA
// See https://www.kernel.org/doc/Documentation/spi/spidev for more information on SPIDEV


/**************************************************************/

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t addresses[2] = {0xABCDABCD71LL, 0x33746E6C63LL};

uint8_t data[32];
unsigned long startTime, stopTime, counter, rxTimer = 0;

int main(int argc, char** argv)
{
    bool role_ping_out = 1, role_pong_back = 0;
    bool role = 0;

	char sndBuf[32];
    // Print preamble:

    cout << "RF24/examples/Transfer/\n";

    radio.begin();                           // Setup and configure rf radio
    radio.setChannel(0);
    radio.setPALevel(RF24_PA_MAX);
    radio.setDataRate(RF24_1MBPS);
    radio.setAutoAck(1);                     // Ensure autoACK is enabled
    radio.setRetries(2, 15);                  // Optionally, increase the delay between retries & # of retries
    radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
    radio.printDetails();
/*     // ******** Role chooser ***********

    printf("\n ************ Role Setup ***********\n");
    string input = "";
    char myChar = {0};
    cout << "Choose a role: Enter 0 for receiver, 1 for transmitter (CTRL+C to exit)\n>";
    getline(cin, input);

    if (input.length() == 1) {
        myChar = input[0];
        if (myChar == '0') {
            cout << "Role: Pong Back, awaiting transmission " << endl << endl;
        } else {
            cout << "Role: Ping Out, starting transmission " << endl << endl;
            role = role_ping_out;
        }
    }
    // ***********************************

    if (role == role_ping_out) {
        radio.openWritingPipe(addresses[1]);
        radio.openReadingPipe(1, addresses[0]);
        radio.stopListening();
    } else {
        radio.openWritingPipe(addresses[0]);
        radio.openReadingPipe(1, addresses[1]);
        radio.startListening();
    } */

    for (int i = 0; i < 32; i++) {
        data[i] = rand() % 255;                        //Load the buffer with random data
    }

    // forever loop
    while (1) {
		
      std::this_thread::sleep_for(1s);
      string recPacket = udpListener.GetNextPacket();
      
      if (recPacket.compare(""))
      {
        strcpy(sndBuf, recPacket.c_str());

        if (!radio.writeFast(&sndBuf, 32)) {     //Write to the FIFO buffers
          counter++;                      //Keep count of failed payloads
        }
      }

/*
        if (role == role_ping_out) {
            sleep(2);
            printf("Initiating Basic Data Transfer\n\r");

            long int cycles = 1000;                    //Change this to a higher or lower number.

            // unsigned long pauseTime = millis();		//Uncomment if autoAck == 1 ( NOACK )
            startTime = millis();

            for (int i = 0; i < cycles; i++) {                //Loop through a number of cycles
                data[0] = i;                        //Change the first byte of the payload for identification
                if (!radio.writeFast(&data, 32)) {     //Write to the FIFO buffers
                    counter++;                      //Keep count of failed payloads
                }


                //This is only required when NO ACK ( enableAutoAck(0) ) payloads are used
                //		if(millis() - pauseTime > 3){       // Need to drop out of TX mode every 4ms if sending a steady stream of multicast data
                 //           pauseTime = millis();
                   //         radio.txStandBy();				// This gives the PLL time to sync back up
                     //   }
            }
            stopTime = millis();

            if (!radio.txStandBy()) {
                counter += 3;
            }

            float numBytes = cycles * 32;
            float rate = numBytes / (stopTime - startTime);

            printf("Transfer complete at %.2f KB/s \n\r", rate);
            printf("%lu of %lu Packets Failed to Send\n\r", counter, cycles);
            counter = 0;

        }

        if (role == role_pong_back) {
            while (radio.available()) {
                radio.read(&data, 32);
                counter++;
            }
            if (millis() - rxTimer > 1000) {
                rxTimer = millis();
                printf("Rate: ");
                float numBytes = counter * 32;
                printf("%.2f KB/s \n\r", numBytes / 1000);
                printf("Payload Count: %lu \n\r", counter);
                counter = 0;
            }
        }
		*/

    } // loop
} // main






