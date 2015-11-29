#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// todo: update to use proper pin mapping...
#define DATA_PIN  2
#define CLOCK_PIN 3

const int ledPin =  13;      // the number of the LED pin

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() 
{ 
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial1.begin(1000000);

  // run all channels at once...
  FastLED.addLeds<WS2801, 2, 3, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2801, 4, 5, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2801, 6, 7, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2801, 8, 9, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2801, 10, 11, RGB>(leds, NUM_LEDS);
  FastLED.addLeds<WS2801, 12, 13, RGB>(leds, NUM_LEDS);
}

void myfill(CRGB color)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = color;
  }  
}

// test routine to at least test all individual LEDs...
void loop() 
{
  Serial1.print("hello");

  // Turn the LED on, then pause
  myfill(CRGB::Red);
  FastLED.show();
  digitalWrite(ledPin, HIGH);
  Serial.print("all red\r\n");
  delay(5000);

  // Now turn the LED off, then pause
  myfill(CRGB::Black);
  FastLED.show();
  digitalWrite(ledPin, LOW);
  Serial.print("all black\r\n");
  delay(1000);

  myfill(CRGB::Blue);
  FastLED.show();
  digitalWrite(ledPin, HIGH);
  Serial.print("all blue\r\n");
  delay(5000);

  // Now turn the LED off, then pause
  myfill(CRGB::Black);
  FastLED.show();
  digitalWrite(ledPin, LOW);
  Serial.print("all black\r\n");
  delay(1000);
  
  // Turn the LED on, then pause
  myfill(CRGB::Green);
  FastLED.show();
  digitalWrite(ledPin, HIGH);
  Serial.print("all green\r\n");
  delay(5000);
  
  // Now turn the LED off, then pause
  myfill(CRGB::Black);
  FastLED.show();
  digitalWrite(ledPin, LOW);
  Serial.print("all black\r\n");
  delay(1000);


  // Turn the LED on, then pause
  myfill(CRGB::White);
  FastLED.show();
  digitalWrite(ledPin, HIGH);
  Serial.print("all green\r\n");
  delay(5000);
  
  // Now turn the LED off, then pause
  myfill(CRGB::Black);
  FastLED.show();
  digitalWrite(ledPin, LOW);
  Serial.print("all black\r\n");
  delay(1000);
  
}


