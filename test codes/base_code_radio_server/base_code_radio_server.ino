/*
  Arduino Wireless Network - Multiple NRF24L01 Tutorial
          == Base/ Master Node 00==
  by Dejan, www.HowToMechatronics.com
  Libraries:
  nRF24/RF24, https://github.com/nRF24/RF24
  nRF24/RF24Network, https://github.com/nRF24/RF24Network
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>


RF24 radio(9, 10);               // nRF24L01 (CE,CSN)

// you either use address bytes to communicate directly
//const byte address[6] = "00001"; // address is the same as client

// or create a network
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;      // Address of the other node in Octal format


void setup() {
  Serial.begin(9600);
  
  // code for address byte
  /*
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  */

  // code for network
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
}

void loop() {
  // code for address byte
  /*
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  delay(1000);
  */

  // code for radio network
  network.update();
  //===== Sending =====//
  //const char text[] = "Hello World";
  int text = 1;
  Serial.println("");
  Serial.print("Sending to node 1: ");
  Serial.print(text);
  RF24NetworkHeader header2(node01);     // (Address where the data is going)
  bool ok = network.write(header2, &text, sizeof(text)); // Send the data

  int incomingData = 0;
  RF24NetworkHeader header;
  network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
  Serial.println("");
  Serial.print("Data recieved in and sent from node 1: ");
  Serial.print(incomingData);
  delay(1000);
}
