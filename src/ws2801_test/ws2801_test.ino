#include "FastLED.h"

// How many leds in your strip?
#define NUM_LEDS 50

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// todo: update to use proper pin mapping...
#define DATA_PIN  3
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() 
{ 
  FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
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
  // Turn the LED on, then pause
  myfill(CRGB::Red);
  FastLED.show();
  delay(500);

  // Now turn the LED off, then pause
  myfill(CRGB::Black);
  FastLED.show();
  delay(500);

  myfill(CRGB::Blue);
  FastLED.show();
  delay(500);

  // Now turn the LED off, then pause
  myfill(CRGB::Black);
  FastLED.show();
  delay(500);
  
  // Turn the LED on, then pause
  myfill(CRGB::Green);
  FastLED.show();
  delay(500);
  
  // Now turn the LED off, then pause
  myfill(CRGB::Black);
  FastLED.show();
  delay(500);
}
