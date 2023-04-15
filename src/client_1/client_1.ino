// Import libraries
#include <Adafruit_NeoPixel.h> // for LED
#include <RF24Network.h>
#include <RF24.h>
#include <SPI.h>


// LED initialisation pins
int NUMSTRIPS = 3; // total there's 2 strips
int NUMPIXELS = 6; // number of neopixels connected

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel strips[3] = {
    Adafruit_NeoPixel(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, 3, NEO_GRB + NEO_KHZ800),
    //Adafruit_NeoPixel(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, 5, NEO_GRB + NEO_KHZ800),
};


// Radio pins initialisation
RF24 radio(10, 9); // nRF24L01 (CE,CSN)
RF24Network network(radio);      // Include the radio in the network
const uint16_t this_node = 01;   // Address of our node in Octal format ( 04,031, etc)
const uint16_t master00 = 00;    // Address of the other node in Octal format


// Functions declaration
void light_0(); // lights up the first strip
void light_1(); // lights up the second strip
void light_2(); // lights up the third strip
void light_off(int k); // turns off a particular strip k
void light_up(); // lights up all the strips from lowest to highest
void light_down(); // lights up all the strips from highest to lowest
void light_blink_left(); // lights up the strip one by one from right to left
void light_blink_right(); // lights up the strip one by one from left to right
void light_run(); // neopixel running effect


void setup() {
  Serial.begin(115200);

  // NeoPixel library initialisation
  for (int i=0; i<NUMSTRIPS; i++){
    strips[i].begin();
    // default all pixels to off
    strips[i].show(); 
  }

  // code for radio network
  SPI.begin();
  radio.begin();
  network.begin(90, this_node);  //(channel, node address)
  radio.setDataRate(RF24_2MBPS);
  Serial.println("Client 2 initialised\nListenning to signal...\n");
}

void loop() {
  network.update();
  
  //===== Receiving =====//
  while ( network.available() ) { // Is there any incoming data?
    RF24NetworkHeader header;
    int incomingData = 0;
    network.read(header, &incomingData, sizeof(incomingData)); // Read the incoming data
    Serial.println(incomingData);

    if (incomingData==1){
      // if up gesture, light the strips from lowest to highest
      light_up();
    }
    else if (incomingData==2){
      // if down gesture, light the strips from highest to lowest
      light_down();
    }
    else if (incomingData==3){
      // if left gesture, light up the strips one by one from right to left
      light_blink_left();
    }
    else if (incomingData==4){
      // if right gesture, light up the strips one by one from left to right
      light_blink_right();
    }
    else if (incomingData==5){
      light_run();
    }
  }
}

// Functions definition
// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
// Note: LED output may be different from the rgb code used (ie crimson may look like orange)

void light_0(){
  for (int p=0; p<NUMPIXELS; p++){
    strips[0].setPixelColor(p, strips[0].Color(255,243,225)); // colour: almond
  }
  strips[0].show();
  Serial.println("light 0 lit");
}

void light_1(){
  for (int p=0; p<NUMPIXELS; p++){
    strips[1].setPixelColor(p, strips[1].Color(220,20,60)); // colour: crimson
  }
  strips[1].show();
  Serial.println("light 1 lit");
}

void light_2(){
  for (int p=0; p<NUMPIXELS; p++){
    strips[2].setPixelColor(p, strips[2].Color(218,165,32)); // colour: goldenrod
  }
  strips[2].show();
  Serial.println("light 2 lit");
}


void light_off(int k){
  strips[k].clear();
  strips[k].show();
}


void light_up(){
  light_1();
  delay(200);
  light_off(1);
  // -------
  delay(200);
  // -------
  light_2();
  delay(200);
  light_off(2);
  // -------
  light_0();
  delay(200);
  light_off(0);
}


void light_down(){
  // -------
  delay(200);
  // -------
  light_0();
  delay(200);
  light_off(0);
  // -------
  light_2();
  delay(200);
  light_off(2);
  // -------
  light_1();
  delay(200);
  light_off(1);
}


void light_blink_left(){
  // lights up the strip one by one from right to left
  light_2();
  delay(200);
  light_off(2);
  // -------
  delay(400);
  // -------
  light_1();
  delay(200);
  light_off(1);
  // -------
  delay(400);
  // -------
  light_0();
  delay(200);
  light_off(0);
}


void light_blink_right(){
  // lights up the strip one by one
  delay(200);
  // -------
  light_0();
  delay(200);
  light_off(0);
  // -------
  delay(400);
  // -------
  light_1();
  delay(200);
  light_off(1);
  // -------
  delay(400);
  // -------
  light_2();
  delay(200);
  light_off(2);
}


void light_run(){
  for (int k=0; k<NUMSTRIPS; k++){
    for (int p=0; p<NUMPIXELS-1; p++){
      strips[k].setPixelColor(p, strips[k].Color(218,165,32)); // colour: goldenrod
      strips[k].show();
      delay(100);
      strips[k].setPixelColor(p+1, strips[k].Color(218,165,32));
      strips[k].show();
      delay(100);
      strips[k].setPixelColor(p, strips[k].Color(0,0,0));
    }
  }
  light_off(0);
  light_off(1);
  light_off(2);
}
