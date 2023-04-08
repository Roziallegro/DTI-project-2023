// Import libraries
#include <Adafruit_NeoPixel.h> // for LED
#include <Wire.h> // for hand gesture sensor
#include "paj7620.h"


// LED initialisation pins
int NUMSTRIPS = 2; // total there's 2 strips
int NUMPIXELS = 6; // number of neopixels connected

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strips[2] = {
    Adafruit_NeoPixel(NUMPIXELS, 6, NEO_GRB + NEO_KHZ800),
    Adafruit_NeoPixel(NUMPIXELS, 7, NEO_GRB + NEO_KHZ800)
};

//int delayval = 500; // delay for half a second


// Reaction time initialisation
int GES_REACTION_TIME = 100; // adjust reaction time according to circumstance
int GES_ENTRY_TIME = 100; // when recognising Forward/Backward gestures, reaction time must be less than GES_ENTRY_TIME(0.8s) 
int GES_QUIT_TIME = 200;


// Functions declaration
void forward(); // gets called when a gesture of 'forward' is recognised
void backward(); // gets called when a gesture of 'backward' is recognised
void left(); // gets called when a gesture FROM LEFT to right is recognised
void right(); // gets called when a gesture FROM RIGHT to left is recognised


void setup() {
  // NeoPixel library initialisation
  strips[1].begin();
  strips[2].begin();  

  // Paj7620 initialisation & error handling
  uint8_t error = 0;
  Serial.begin(9600);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  error = paj7620Init();      
  if (error) {
      Serial.print("INIT ERROR,CODE:");
      Serial.println(error);
   } else {
       Serial.println("INIT OK");
   }
    Serial.println("Please input your gestures:\n");
}


void loop() {
  uint8_t data = 0, data1 = 0, error;
  error = paj7620ReadReg(0x43, 1, &data); // Read Bank_0_Reg_0x43/0x44 for gesture result
  
  if (!error) {
      switch (data) {  // When different gestures be detected, the variable 'data' will be set to different values by paj7620ReadReg(0x43, 1, &data)
          case GES_RIGHT_FLAG:
              delay(GES_ENTRY_TIME);
              paj7620ReadReg(0x43, 1, &data);
              
              if (data == GES_FORWARD_FLAG) {
                  Serial.println("Forward");
                  // add forward code here
                  delay(GES_QUIT_TIME);
                  
              } else if (data == GES_BACKWARD_FLAG) {
                  Serial.println("Backward");
                  // backward function
                  delay(GES_QUIT_TIME);
                 
               } else {
                  Serial.println("Right"); // Note: from right to left
                  // right function
                }
                break;
                
            case GES_LEFT_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                
                if (data == GES_FORWARD_FLAG) {
                    Serial.println("Forward");
                    // add forward code here
                    delay(GES_QUIT_TIME);
                    
                } else if (data == GES_BACKWARD_FLAG) {
                    Serial.println("Backward");
                    // backward function
                    delay(GES_QUIT_TIME);
                    
                } else {
                    Serial.println("Left");
                    // left function
                }
                break;
                
            case GES_UP_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_FORWARD_FLAG) {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                } else if (data == GES_BACKWARD_FLAG) {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                } else {
                    Serial.println("Up");
                }
                break;
            case GES_DOWN_FLAG:
                delay(GES_ENTRY_TIME);
                paj7620ReadReg(0x43, 1, &data);
                if (data == GES_FORWARD_FLAG) {
                    Serial.println("Forward");
                    delay(GES_QUIT_TIME);
                } else if (data == GES_BACKWARD_FLAG) {
                    Serial.println("Backward");
                    delay(GES_QUIT_TIME);
                } else {
                    Serial.println("Down");
                }
                break;
            case GES_FORWARD_FLAG:
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
                break;
            case GES_BACKWARD_FLAG:
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
                break;
            case GES_CLOCKWISE_FLAG:
                Serial.println("Clockwise");
                break;
            case GES_COUNT_CLOCKWISE_FLAG:
                Serial.println("anti-clockwise");
                break;
            default:
                paj7620ReadReg(0x44, 1, &data1);
                if (data1 == GES_WAVE_FLAG) {
                    Serial.println("wave");
                }
                break;
        }
    }
    delay(100);
}


// Functions initilisation
void forward(){
  for (int pixel=0, pixel<NUMPIXELS, pixel++){
    for (int strip=0, strip<NUMSTRIPS, strip++){
      
    }
  }
  strips[1].setPixelColor(0, pixels.Color(150,0,0));
}
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  pixels.setPixelColor(0, pixels.Color(150,0,0)); // red at about 60% of full brightness
  pixels.setPixelColor(1, pixels.Color(0,150,0)); // green at about 60% of full brightness
  pixels.setPixelColor(2, pixels.Color(0,0,150)); // blue at about 60% of full brightness
  pixels.setPixelColor(3, pixels.Color(50,50,50)); // white at about 20% of full brightness
  pixels.setPixelColor(4, pixels.Color(0,0,0)); // off
  pixels.setPixelColor(5, pixels.Color(25,25,25)); // magenta

  pixels.show(); // This sends the updated pixel color to the hardware.
