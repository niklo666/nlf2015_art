#include <FastLED.h>

const int num_leds_channel0 = 50; //
const int num_leds_channel1 = 50; // 
const int num_leds_channel2 = 50; // 
const int num_leds_channel3 = 50; // 
const int num_leds_channel4 = 50; // 
const int num_leds_channel5 = 50; // 

CRGB leds_channel0[num_leds_channel0];
CRGB leds_channel1[num_leds_channel1];
CRGB leds_channel2[num_leds_channel2];
CRGB leds_channel3[num_leds_channel3];
CRGB leds_channel4[num_leds_channel4];
CRGB leds_channel5[num_leds_channel5];

void setup() 
{
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  //Serial1.begin(115200);     // opens serial port, sets data rate to 9600 bps

  FastLED.addLeds<WS2801, 2, 3,   RGB>(leds_channel0, num_leds_channel0);
  FastLED.addLeds<WS2801, 4, 5,   RGB>(leds_channel1, num_leds_channel1);
  FastLED.addLeds<WS2801, 6, 7,   RGB>(leds_channel2, num_leds_channel2);
  FastLED.addLeds<WS2801, 8, 9,   RGB>(leds_channel3, num_leds_channel3);
  FastLED.addLeds<WS2801, 10, 11, RGB>(leds_channel4, num_leds_channel4);
  FastLED.addLeds<WS2801, 12, 13, RGB>(leds_channel5, num_leds_channel5);
}

void command_handler(char* buffer, int size);

char buffer[128];
int buffer_counter = 0;

void loop() 
{
  char incomingByte;
  
  if (Serial.available() > 0) 
  {
    // read the incoming byte:
    incomingByte = Serial.read();

    // check for \r and/or \n...
    if (incomingByte == '\r')  // handle windows...
    {
      // do nothing...
    }
    else if (incomingByte == '\n')  // take care of the actual new line...
    {
      // todo: check for overflow...
      buffer[buffer_counter++] = '0';
      Serial.print("I received: ");
      Serial.print(buffer);

      command_handler(buffer, buffer_counter);

      // reset and start over...
      buffer_counter = 0;
    }
    else
    {
      // todo: check for overflow...
      buffer[buffer_counter++] = incomingByte;
    }
  
    // say what you got:
    Serial.print("I received: ");
    Serial.print(incomingByte);
   }
}


void command_handler(char* buffer, int size)
{
  /*
    command structure:
    set color <group> <r>,<g>,<b>
  */ 
  int group = 0;
  int red   = 0;
  int green = 0;
  int blue  = 0;
  char* token;

  // 1st...
  token = strtok(buffer, " ,");

  if (!strcmp("set", token))
  { 
    // 2nd
    token = strtok(NULL, " ,");
  
    if (strcmp("color", token))
    {
      Serial.print("unknown input: ");
      Serial.print(token);
    }
  
    // 3rd...
    token = strtok(NULL, " ,");
    group = atoi(token);

    // 4th
    token = strtok(NULL, " ,");
    red = atoi(token);

    // 5th
    token = strtok(NULL, " ,");
    green = atoi(token);

    // 6th
    token = strtok(NULL, " ,");
    blue = atoi(token);

    Serial.print("group: ");
    Serial.print(group);
    Serial.print("\r\n");
    
    Serial.print("red: ");
    Serial.print(red);
    Serial.print("\r\n");
    
    Serial.print("green: ");
    Serial.print(green);
    Serial.print("\r\n");
    
    Serial.print("blue: ");
    Serial.print(blue);
    Serial.print("\r\n");

    // todo: sanity check...

    // create CRGB...
    CRGB color;
    color.r = red;
    color.g = green;
    color.b = blue;

    // todo: update to handle all (at least the used ones) channels...
    fill_solid(leds_channel0, num_leds_channel0, color);
    FastLED.show();
  }
  else if (!strcmp("help", token))
  {
    Serial.print("usage:\r\n");
    Serial.print("set color <group> <r>,<g>,<b>\r\n");
    Serial.print("<group> - group id 0-5\r\n");
    Serial.print("<r>,<g>,<b> - red, green, blue color values 0-255\r\n");
  }
  else
  {
    Serial.print("unknown input: ");
    Serial.print(token);
    Serial.print("\r\n");
  }
}

