/*
  light_node.ino
*/

#include <SPI.h>
#include <QueueList.h>
// todo: use fastled...
// todo: remove dotstar...
//#include <Adafruit_NeoPixel.h>
//#include <Adafruit_DotStar.h>
#include "FastLED.h"
// below doesn't work but has been taken care of...
//#include "../../shared/light_protocol.h"
#include "light_protocol.h"


/*
  light areas and their behaviours (normal):
  - strands, patterns and palettes also variable in intensity...
  - text, static color with variable intensity
  - circle ambient, static color variable intensity...
  - lips, static color with variable intensity...
  - eyes, static color with variable intensity...
  - mains, no color control but dimmable...

  this stuff (scenarios) should reside in main controller. the light controller only do "simple" stuff...
  the only advanced stuff is handling of (slow) dimming and flickering effects...

  light node
  lighting behaviour needed/wanted:
  - "static" color, used for dna strand, only subject to dimming and possibly "living" colors i.e. glimmering effect using random colors from palette
  - "static" colors, used for mouths and eyes AND TEXT!?, probably only dimming with one static color per item

  example and ideas of commands:
  - set light source color/intensity for group...
  - adjust light source intensity for group, all?
  - activate "pattern"/behaviour on group e.g. "flickering", "randomness"
  - all off...

  todo: update pin mapping:
  3   light channel 0 clock
  2   light channel 0 data
  5   light channel 1 clock
  4   light channel 1 data
  7   light channel 2 clock
  6   light channel 2 data
  9   light channel 3 clock
  8   light channel 3 data
  11  light channel 4 clock
  10  light channel 4 data
  13  light channel 5 clock
  12  light channel 5 data
  TBD mains zero detect
  TBD mains dimmer control 0
  TBD mains dimmer control 1
  TBD mains dimmer control 2
  TBD i2c sda
  TBD i2c scl

*/

// pin definitions...
const int activity_led_pin      = 13; // the number of the LED pin
const int light_channel0_clock  = 3;
const int light_channel0_data   = 4;
const int light_channel1_clock  = 5;
const int light_channel1_data   = 4;
const int light_channel2_clock  = 7;
const int light_channel2_data   = 6;
const int light_channel3_clock  = 9;
const int light_channel3_data   = 8;
const int light_channel4_clock  = 11;
const int light_channel4_data   = 10;
const int light_channel5_clock  = 13;   // todo: possible collision with activity LED...
const int light_channel5_data   = 12;

// led data...
const int strands_number_of_leds = 200;     // for now assume all strands are in serial...
const int lips_number_of_leds = 150;        // for now assume all three symbols use 50 LEDs and are in serial...
const int eyes_number_of_leds = 100;        // for now assume both symbols use 50 LEDs and are in serial...
const int text_group0_number_of_leds = 50;  // one strand to light up "In Lust"...
const int text_group1_number_of_leds = 50;  // one strand to light up "We Trust"...
CRGB strand_leds[strands_number_of_leds];   // number of leds in the strands...
CRGB lips_leds[lips_number_of_leds];   // number of leds in the strands...
CRGB eyes_leds[eyes_number_of_leds];   // number of leds in the strands...
CRGB text_group0_leds[text_group0_number_of_leds];   // number of leds in the strands...
CRGB text_group1_leds[text_group1_number_of_leds];   // number of leds in the strands...

// communication...
light_node_cmd_message_t  g_command_buffer;
uint8_t                   g_command_buffer_valid = 0;
  

void setup()
{
  // init on-board teensy LED to use as activity indicator...
  pinMode(activity_led_pin, OUTPUT);

  // init lighting stuff...
  // - todo: init mains power control(dimmer) io and see to that power is turned off...
  // - todo: init camera node power control...
  // - init ws2801 control io and see to that leds are off...
  FastLED.addLeds<WS2801, light_channel0_data, light_channel0_clock, RGB>(strand_leds, strands_number_of_leds);
  FastLED.addLeds<WS2801, light_channel1_data, light_channel1_clock, RGB>(lips_leds, lips_number_of_leds);
  FastLED.addLeds<WS2801, light_channel2_data, light_channel2_clock, RGB>(eyes_leds, eyes_number_of_leds);
  FastLED.addLeds<WS2801, light_channel3_data, light_channel3_clock, RGB>(text_group0_leds, text_group0_number_of_leds);
  FastLED.addLeds<WS2801, light_channel4_data, light_channel4_clock, RGB>(text_group1_leds, text_group1_number_of_leds);

  // todo: init datastructures...

  // init debug serial port...
  Serial.begin(9600);

  // init rpi communication port...
  // todo: selecty proper serial port speed...
  Serial1.begin(1000000, SERIAL_8N1);
}

void communication_handler(void);
void command_handler(void);
void light_handler(void);

void loop()
{
  // put your main code here, to run repeatedly:

  // todo: react on communication input(s)...
  // collect command packets...
  communication_handler();

  command_handler();

  // todo: do autonomous stuff e.g. dimming, contingency/"idle" mode behaviour...
  // todo: update lighting...
  light_handler();
}


// todo: init...
void communication_init(void)
{
//  Serial1.begin();
}

//
void communication_handler(void)
{
  static uint8_t buffer_counter = 0;
  static uint8_t buffer[2*sizeof(light_node_cmd_message_t)];
  light_node_cmd_message_t* ptr = 0;

  // copy to buffer...
  while ((buffer_counter < sizeof(light_node_cmd_message_t)) && Serial1.available())
  {
    buffer[buffer_counter] = Serial1.read();
  }

  if (buffer_counter < (sizeof(light_node_cmd_message_t)))
  {
    // not a full packet...
    // leave it for next round to handle...
    return;
  }

  // todo: sanity check...

  // todo: try to assemble packet..
  // todo: if successful, queue...
  ptr = (light_node_cmd_message_t*)buffer;
  //g_incoming_command_queue.push(*ptr); // todo: doesn't work...
  // todo: queue the message...
  for (int i =0; i< sizeof(light_node_cmd_message_t); i++)
  {
    g_command_buffer[i] = (*ptr)[i];
  }

  // todo: sanity check...

  g_command_buffer_valid = 1;
}

void command_handler(void)
{
  light_node_resp_message_t response;
  
  if (!g_command_valid)
  {
    return;
  }

  // copy the command code...
  response.command = g_command_buffer.command;
  response.start_magic  = LIGHT_NODE_MESSAGE_START_MAGIC;
  response.stop_magic   = LIGHT_NODE_MESSAGE_STOP_MAGIC;
  
  switch (g_command_buffer.command)
  {
    // todo: implement commands...
    case LIGHT_NODE_COMMAND_NONE:
      // do nothing but give some response...
      response.status = 0;

    default:
      response.status = ;
  }
}

//
//
//
void light_handler(void)
{
  // todo: do autonomous stuff like dimming, patterns etc...

  // todo: update the actual lights...
}
