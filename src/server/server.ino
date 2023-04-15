// Import libraries
#include <Wire.h> // for hand gesture sensor
#include "paj7620.h"
#include <RF24Network.h> // for radio sensor
#include <RF24.h>
#include <SPI.h>


// Radio pin & address initialisation
RF24 radio(9, 10);               // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 00;   // Address of this node in Octal format ( 04,031, etc)
const uint16_t node01 = 01;      // Address of the other nodes in Octal format
const uint16_t node02 = 02; 
const uint16_t node03 = 03; 


// Ultrasonic pin initialisation
int trigPin = 8; 
int echoPin = 7;
float duration_us, distance_cm;   


// Functions declaration
void send_signal_up(int movement[0]); // gets called when a recognised gesture is sent to nodes
void send_signal_down(int movement[0]);
void send_signal_leftright(int movement[0]);
// a moving hand will get picked up by the gesture sensor 
//while a hovering (stationary) hand will get picked up by the ultrasonic sensor
void send_signal_run();

// Note: this code does not recognise clockwise and anti-clockwise gestures


void setup() {
  // Paj7620 initialisation & error handling
  uint8_t error = 0;
  Serial.begin(115200);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  error = paj7620Init();      
  if (error) {
      Serial.print("INIT ERROR,CODE:");
      Serial.println(error);
   } else {
       Serial.println("INIT OK");
   }
   Serial.println("Please input your gestures:\n");
    
  //NRF24L01 initialisation
  SPI.begin();
  radio.begin();
  network.begin(90, this_node); //(channel, node address)
  radio.setDataRate(RF24_2MBPS);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
}

  
void loop() {
  network.update();
  
  uint8_t data = 0, error;
  // Read Bank_0_Reg_0x43/0x44 for gesture result
  error = paj7620ReadReg(0x43, 1, &data);
  if (!error)
  {
    //Serial.println(data);
    // gesture detected -> stored to variable 'data' by paj7620ReadReg(0x43, 1, &data)
    
    // if no gesture detected, paj7620 will register 0
    if (data == 0){
      // send signal to ultrasonic & check if a hand is nearby (within 5cm range from sensor)
      // generate 10-microsecond pulse to TRIG pin
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);

      // measure duration of pulse from ECHO pin
      duration_us = pulseIn(echoPin, HIGH);
      
      // calculate the distance
      distance_cm = 0.017 * duration_us;
      
      // print the value to Serial Monitor
      /*
      Serial.print("distance: ");
      Serial.print(distance_cm);
      Serial.println(" cm");
      */

      if (1.00 <= distance_cm && distance_cm <= 5.00){
        send_signal_run();
        Serial.println("Hand above");
      }
      delay(200);
    }
    else{
       switch (data) {
        case GES_RIGHT_FLAG:
          Serial.println("Up to Down");
          send_signal_leftright(2);
          delay(200); 
          break;
        case GES_LEFT_FLAG:
          Serial.println("Down to Up");
          send_signal_leftright(1);
          delay(200);
          break;
        case GES_UP_FLAG:
          Serial.println("Left to Right");
          send_signal_down(4);
          delay(200);
          break;
        case GES_DOWN_FLAG:
          Serial.println("Right to Left");
          send_signal_up(3);
          delay(200);
          break;
      }
    }
  }
  delay(200);
}

// Functions definition
// sends the movement recorded by the hand gesture sensor to the nodes
void send_signal_up(int movement[0]){
  RF24NetworkHeader header1(node01);  // header => address where the data is going
  network.write(header1, &movement, sizeof(movement)); // send the data
  delay(400);
  RF24NetworkHeader header2(node02);
  network.write(header2, &movement, sizeof(movement));
  delay(400);
  RF24NetworkHeader header3(node03);
  network.write(header3, &movement, sizeof(movement));
}

void send_signal_down(int movement[0]){
  RF24NetworkHeader header3(node03);  // header => address where the data is going
  network.write(header3, &movement, sizeof(movement)); // send the data
  delay(400);
  RF24NetworkHeader header2(node02);
  network.write(header2, &movement, sizeof(movement));
  delay(400);
  RF24NetworkHeader header1(node01);
  network.write(header1, &movement, sizeof(movement));
}

void send_signal_leftright(int movement[0]){
  RF24NetworkHeader header1(node01);  // header => address where the data is going
  network.write(header1, &movement, sizeof(movement)); // send the data
  delay(100);
  RF24NetworkHeader header2(node02);
  network.write(header2, &movement, sizeof(movement));
  delay(100);
  RF24NetworkHeader header3(node03);
  network.write(header3, &movement, sizeof(movement));
}

void send_signal_run(){
  int movement = 5;
  RF24NetworkHeader header1(node01);  // header => address where the data is going
  network.write(header1, &movement, sizeof(movement)); // send the data
  RF24NetworkHeader header2(node02);
  network.write(header2, &movement, sizeof(movement));
  RF24NetworkHeader header3(node03);
  network.write(header3, &movement, sizeof(movement));
}
