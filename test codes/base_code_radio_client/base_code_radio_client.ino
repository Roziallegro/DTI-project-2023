/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(9, 10); // CE, CSN

// you either use address bytes to communicate directly
//const byte address[6] = "00001";

// or create a network
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format

void setup() {
  Serial.begin(9600);

  // code for address bytes
  /*
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  */

  // code for radio network
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
}

void loop() {
  // code for address bytes
  /*
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
  */

  // code for radio network
  network.update();
  //===== Receiving =====//
  while ( network.available() ) {     // Is there any incoming data?
    RF24NetworkHeader header;
    //char incomingData[32] = "";
    int incomingData = 0;
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    Serial.println("");
    Serial.println("Signal received from node 00: ");
    Serial.print(incomingData);
    
    RF24NetworkHeader header1(master00);
    network.write(header1, &incomingData, sizeof(incomingData));
  }
}
