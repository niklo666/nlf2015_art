/*
  light_node.ino
*/

#include <SPI.h>
#include <QueueList.h>
#include "FastLED.h"
#include <elapsedMillis.h>
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

  update pin mapping:
  2   light channel 0 data    - strands front i.e. lips
  3   light channel 0 clock   
  4   light channel 1 data    - strands rear i.e. eyes
  5   light channel 1 clock
  6   light channel 2 data    - eyes 
  7   light channel 2 clock
  8   light channel 3 data    - lips
  9   light channel 3 clock
  10  light channel 4 data    - text0 "IN LUST"
  11  light channel 4 clock
  12  light channel 5 data    - text1 "WE TRUST"
  13  light channel 5 clock
  
  TBD dimmer control          - control of relay to maneuver a regular button dimmer...
  TBD i2c sda
  TBD i2c scl

*/

enum
{
  LIGHT_SOURCE_STATUS_NORMAL    = 0,
  LIGHT_SOURCE_STATUS_DIM       = 0,
  LIGHT_SOURCE_STATUS_BRIGHTEN  = 0,
};

typedef struct
{
  int     status;       // 
  uint8_t speed;        // dim/brighten speed in steps per 100ms...
  uint8_t start_value;  
  uint8_t max_value; 
}light_source_behaviour_t;


// pin definitions...
const int activity_led_pin      = 13; // the number of the LED pin

const int light_channel0_clock  = 3; 
const int light_channel0_data   = 2;
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
const int strands_front_number_of_leds  = 100;      // split in half...
const int strands_rear_number_of_leds   = 100;      // split in half...
const int eyes_number_of_leds           = 100;      // for now assume both symbols use 50 LEDs and are in serial...
const int lips_number_of_leds           = 150;      // for now assume all three symbols use 50 LEDs and are in serial...
const int text0_number_of_leds          = 50;       // one strand to light up "In Lust"...
const int text1_number_of_leds          = 50;       // one strand to light up "We Trust"...
CRGB front_strand_leds[strands_front_number_of_leds];           // number of leds in the strands...
CRGB rear_strand_leds[strands_rear_number_of_leds];           // number of leds in the strands...
CRGB eyes_leds[eyes_number_of_leds];                // number of leds in the strands...
CRGB lips_leds[lips_number_of_leds];                // number of leds in the strands...
CRGB text0_leds[text0_number_of_leds];              // number of leds in the strands...
CRGB text1_leds[text1_number_of_leds];              // number of leds in the strands...

light_source_behaviour_t strands_behaviour = {0,0,0,0};
light_source_behaviour_t eyes_behaviour = {0,0,0,0};
light_source_behaviour_t lips_behaviour = {0,0,0,0};
light_source_behaviour_t text0_behaviour = {0,0,0,0};
light_source_behaviour_t text1_behaviour = {0,0,0,0};


// communication data...
light_node_cmd_message_t  g_command_buffer;
uint8_t                   g_command_buffer_valid = 0;
light_node_resp_message_t g_response_buffer;

// 
uint8_t g_update_lights  = 0;

// system...
uint32_t g_system_status = 0; // overall system status used to communicate async errors and status changes...

// for periodic stuff...
elapsedMillis g_periodic_timer;


void setup(void)
{
  // init on-board teensy LED to use as activity indicator...
  pinMode(activity_led_pin, OUTPUT);

  // init lighting stuff...
  // - todo: init mains power control(dimmer) io and see to that power is turned off...
  // - todo: init camera node power control...
  // - init ws2801 control io and see to that leds are off...
  FastLED.addLeds<WS2801, light_channel0_data, light_channel0_clock, RGB>(front_strand_leds, strands_front_number_of_leds);
  FastLED.addLeds<WS2801, light_channel1_data, light_channel1_clock, RGB>(rear_strand_leds, strands_rear_number_of_leds);
  FastLED.addLeds<WS2801, light_channel2_data, light_channel2_clock, RGB>(eyes_leds, eyes_number_of_leds);
  FastLED.addLeds<WS2801, light_channel3_data, light_channel3_clock, RGB>(lips_leds, lips_number_of_leds);
  FastLED.addLeds<WS2801, light_channel4_data, light_channel4_clock, RGB>(text0_leds, text0_number_of_leds);
  FastLED.addLeds<WS2801, light_channel5_data, light_channel5_clock, RGB>(text1_leds, text1_number_of_leds);

  // init datastructures...
  // todo: clear command buffer...
  // todo: clear reponse buffer...
  
  // init debug serial port...
  Serial.begin(9600);

  // init rpi communication port...
  // todo: select proper serial port speed...
  // trial and error tells that 115200 works ok!
  Serial1.begin(115200, SERIAL_8N1);
}

int communication_handler(void);
int command_handler(void);
int response_handler(void);
void light_handler(void);


//**************
// main loop...
//**************

void loop()
{
  // init status to ok...
  int ret = LIGHT_NODE_STATUS_OK;
  
  // handle incoming communication and assemble command messages...
  ret = communication_handler();
  if ((ret != LIGHT_NODE_STATUS_OK) || g_command_buffer_valid)
  {
    // check if we have a valid command...
    // note: g_valid_command shall never be set in case of any error!!!
    if (g_command_buffer_valid)
    { 
      // valid command available...
      // handle the command...
      ret = command_handler();
      if (ret == LIGHT_NODE_STATUS_OK)
      {
        // update...
        g_update_light = 1;
      }
    }

    // and now send the response...
    // todo: remember to purge serial port before sending commands from rpi...
    ret = response_handler();
    if (ret != LIGHT_NODE_STATUS_OK)
    {
      // todo: wht to do...
    }
  }
 
  // todo: do autonomous stuff e.g. dimming, contingency/"idle" mode behaviour...
  // todo: update lighting...
  light_handler();
}

// handle any incoming data on serial port...
int communication_handler(void)
{
  char c;
  static uint8_t buffer_counter = 0;
  static char buffer[2 * sizeof(light_node_cmd_message_t)];
  char* ptr = NULL;
  boolean error_flag = false;
  int return_code = LIGHT_NODE_STATUS_OK;

  // copy incoming byte(s) to buffer...
  while ((buffer_counter < sizeof(light_node_cmd_message_t)) && Serial1.available())
  {
    // read byte...
    c = Serial1.read();

    // debug: show what we got...
    Serial.print("rcvd: ");
    Serial.print(c);
    Serial.print("\r\n");

    // store in buffer...
    buffer[buffer_counter] = c;

    // increment counter...
    buffer_counter++;
  }

  // check if ready...
  if (buffer_counter < (sizeof(light_node_cmd_message_t)))
  {
    // not a full packet...
    // leave it for next round to handle...
    Serial.print("msg not ready yet: ");
    Serial.print(buffer_counter);
    Serial.print("\r\n");

    // return...
    return LIGHT_NODE_STATUS_OK;
  }

  // todo: sanity check...

  // try to "assemble" packet..
  ptr = (char*)&g_command_buffer;

  // copy message to message buffer...
  for (int i = 0; i < sizeof(light_node_cmd_message_t); i++)
  {
    ptr[i] = buffer[i];
  }

  // sanity checks...
  if (g_command_buffer.start_magic != LIGHT_NODE_MESSAGE_START_MAGIC)
  {
    Serial.print("error: wrong start magic...");
    error_flag = true;
    return_code = LIGHT_NODE_STATUS_BAD_START_MAGIC;
  }

  if (g_command_buffer.stop_magic != LIGHT_NODE_MESSAGE_STOP_MAGIC)
  {
    Serial.print("error: wrong stop magic...");
    error_flag = true;
    return_code = LIGHT_NODE_STATUS_BAD_STOP_MAGIC;
  }

  // set valid flag accordingly...
  if (error_flag == true)
  {
    g_command_buffer_valid = 0;
  }
  else
  {
    g_command_buffer_valid = 1;
  }

  // init the response message...
  g_response_buffer.start_magic     = LIGHT_NODE_MESSAGE_START_MAGIC;
  g_response_buffer.command         = g_command_buffer.command;
  g_response_buffer.command_status  = return_code;  // in case of success it will possibly be overwritten by any execution statuses...
  g_response_buffer.stop_magic      = LIGHT_NODE_MESSAGE_STOP_MAGIC;

  // also return the code...
  return return_code;
}

int set_light_command_handler(void);
int dim_light_command_handler(void);
int light_off_command_handler(void);

// handle any availbale commands...
int command_handler()
{
//  light_node_resp_message_t response;

/*
  // are there any commands?
  if (!g_command_valid)
  {
    return LIGHT_NODE_STATUS_OK;
  }
*/

  // copy command info to response...
  //response->command      = g_command_buffer.command;
  //response->start_magic  = LIGHT_NODE_MESSAGE_START_MAGIC;
  //response->stop_magic   = LIGHT_NODE_MESSAGE_STOP_MAGIC;

  // handle the commmand...
  switch (g_command_buffer.command)
  {
    // todo: implement commands...
    case LIGHT_NODE_COMMAND_NONE:
      // do nothing but give some response...
      g_response_buffer.command_status = LIGHT_NODE_STATUS_OK;
      break;

    case LIGHT_NODE_COMMAND_STATUS:
      // really the same as none i.e. do nothing but give some response...
      g_response_buffer.command_status = LIGHT_NODE_STATUS_OK;
      break;

    case LIGHT_NODE_COMMAND_SET_LIGHT:
      g_response_buffer.command_status = set_light_command_handler();
      break;

    case LIGHT_NODE_COMMAND_DIM_LIGHT:
      g_response_buffer.command_status = dim_light_command_handler();
      break;

    case LIGHT_NODE_COMMAND_LIGHT_OFF:
      g_response_buffer.command_status = light_off_command_handler();
      break;
      
    default:
      g_response_buffer.command_status = LIGHT_NODE_STATUS_UNKNOWN_COMMAND;
  }

  // always return system status...
  g_response_buffer.system_status = g_system_status;

  return LIGHT_NODE_STATUS_OK;
}

int response_handler(void)
{
  char* ptr = NULL;

  ptr = (char*)&g_response_buffer;

  for (int i =0; i < sizeof(light_node_resp_message_t); i++)
  {
    Serial1.write(*ptr);
    ptr++;  
  }
  
  return LIGHT_NODE_STATUS_OK;
}

void color_fill(CRGB* leds, CRGB color, int num)
{
  for (int i = 0; i < num; i++)
  {
    (*leds)[i] = color;
  }  
}

void strands_random_fill_from_palette(const CRGBPalette256& palette, uint8_t brightness)
{   
    for (int i = 0; i < strands_front_number_of_leds; i++)
    {
        front_strand_leds[i]  = ColorFromPalette(palette, random8(), brightness, LINEARBLEND);
        rear_strand_leds[i]   = ColorFromPalette(palette, random8(), brightness, LINEARBLEND);
    }
}

void strands_random_fill_from_rainbow_palette(uint8_t brightness)
{
  strands_random_fill_from_palette(RainbowColors_p, brightness);
}


int set_light_command_handler(void)
{
  int return_code = LIGHT_NODE_STATUS_OK;
  CRGB color;

  // get color even if we do not use it....
  color.red   = g_command_buffer.color[0];
  color.green = g_command_buffer.color[1];
  color.blue  = g_command_buffer.color[2];  
  
  
  switch (g_command_buffer.light)
  {
    case LIGHT_GROUP_NONE:
      // do nothing...
      return_code = LIGHT_NODE_STATUS_OK;
      break;

    case LIGHT_GROUP_STRANDS:
      // todo: some kind of pattern...
      // random color from rainbow palette at dim level!?
      switch (g_command_buffer.pattern)
      {
          case LIGHT_PATTERN_STATIC:
          default:
            color_fill(front_strand_leds, color, strands_front_number_of_leds); 
            color_fill(rear_strand_leds, color, strands_rear_number_of_leds); 
            break;
      }
      break;

    case LIGHT_GROUP_LIPS:
      // support only static color...
      color_fill(lips_leds, color, lips_number_of_leds); 
      break;
      
    case LIGHT_GROUP_EYES:
      color_fill(eyes_leds, color, eyes_number_of_leds);
      break;
      
    case LIGHT_GROUP_TEXT0:
      color_fill(text0_leds, color, text0_number_of_leds);
      break;
      
    case LIGHT_GROUP_TEXT1:
      color_fill(text1_leds, color, text1_number_of_leds);
      break;
      
    case LIGHT_GROUP_BULBS:
      // todo: implement mains lamp dimming...
      // use red as intensity...
      break;

    default:
      return_code = LIGHT_NODE_STATUS_UNKNOWN_LIGHT;
  }
  
  return return_code;
}

int dim_light_command_handler(void)
{
  // todo: implement...
  return LIGHT_NODE_STATUS_OK;
}

int light_off_command_handler(void)
{
  int return_code = LIGHT_NODE_STATUS_OK;
  
  switch (g_command_buffer.light)
  {
    case LIGHT_GROUP_NONE:
      // do nothing...
      return_code = LIGHT_NODE_STATUS_OK;
      break;

    case LIGHT_GROUP_STRANDS:
      // todo: some kind of pattern...
      // random color from rainbow palette at dim level!?
      switch (g_command_buffer.pattern)
      {
          case LIGHT_PATTERN_STATIC:
          default:
            color_fill(front_strand_leds, BLACK, strands_front_number_of_leds); 
            color_fill(rear_strand_leds, BLACK, strands_rear_number_of_leds); 
            break;
      }
      break;

    case LIGHT_GROUP_LIPS:
      // support only static color...
      color_fill(lips_leds, BLACK, lips_number_of_leds); 
      break;
      
    case LIGHT_GROUP_EYES:
      color_fill(eyes_leds, BLACK, eyes_number_of_leds);
      break;
      
    case LIGHT_GROUP_TEXT0:
      color_fill(text0_leds, BLACK, text0_number_of_leds);
      break;
      
    case LIGHT_GROUP_TEXT1:
      color_fill(text1_leds, BLACK, text1_number_of_leds);
      break;
      
    case LIGHT_GROUP_BULBS:
      // todo: implement mains lamp dimming...
      // use red as intensity...
      break;

    default:
      return_code = LIGHT_NODE_STATUS_UNKNOWN_LIGHT;
  }
  // todo: implement...
  return LIGHT_NODE_STATUS_OK;
}


//
//
//
void light_handler(void)
{
  // todo: do autonomous stuff like dimming, patterns etc...
  if (g_periodic_timer > 100)
  {
    // reset...
    g_periodic_timer = 0;

    // todo: 
  }
  

  // update the actual lights...
  if (g_update_lights)
  {
    FastLED.show();
  }
  
}
