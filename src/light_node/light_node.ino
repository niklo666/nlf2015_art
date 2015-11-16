/*
  light_node.ino
*/

#include <SPI.h>
#include <QueueList.h>
// todo: use fastled...
// todo: remove dotstar...
#include <Adafruit_NeoPixel.h>
#include <Adafruit_DotStar.h>

/*
  todo: update light "areas" and behaviours...
  light areas and their behaviours (normal):
  - strands, patterns and palettes also variable intensity...
  - text, static color and patterns (worms or point with afterglow) with static intensity
  - circle ambient, static color variable intensity...
  - lips, static color variable intensity...
  - eyes, static color variable intensity...
  - mains, no color control but dimmable...

  todo: update to handle scenarios and complex workings...
  this stuff should reside in main controller. the light controller only do "simple" stuff...
  the only advanced stuff is handling of (slow) dimming and flickering effects...

  light node
  lighting behaviour needed/wanted:
  - "static" color, used for dna strand, only subject to dimming and possibly "living" colors i.e. glimmering effect using random colors from palette
  - "static" color, used for strands, possibly more vivid than dna otherwise same or similar
  - "static" colors, used for mouths and eyes, probably only dimming with one static color per item

  communication could be by CAN as it can handle distance and is quite resistant to disturbances *AND* is bidirectional.
  but we will probably go for ttl usart as it is short haul between main controller and light controller!!

  possibly separate applications distributed over several nodes for differens areas.
  in that case a lib should be developed and used.
  a big issue is the not very user-friendlyness of the arduino ide in that you cannot:
  - have several source files
  - cannot easily compile from commandline
  - no real control of library versions etc.

  example and ideas of commands:
  - set light source color/intensity individual, group, all...
  - adjust light source intensity individual, group, all...
  - activate "pattern"/behaviour on (indivdual), group, (all) e.g. "flickering", "randomness"
  - all off...

  todo: update pin mapping:
  TBD   light channel 0 clock
  TBD   light channel 0 data
  TBD   light channel 1 clock
  TBD   light channel 1 data
  TBD   light channel 2 clock
  TBD   light channel 2 data
  TBD   light channel 3 clock
  TBD   light channel 3 data
  TBD   light channel 4 clock
  TBD   light channel 4 data
  TBD   mains zero detect
  TBD   mains dimmer control 0
  TBD   mains dimmer control 1
  TBD   i2c sda
  TBD   i2c scl

*/

void setup()
{
  // put your setup code here, to run once:

  // todo: init lighting stuff...
  // - init power control io and see to that power is turned off...
  // - init ws2801 control io and see to that leds are off...
  // - init dotstar/apa102 io and see to that leds are off...
  // - init datastructures...

  // todo: init comm stuff...
  // - use usart...
}

void communication_handler(void);
void command_handler(void);
void light_handler(void);

void loop()
{
  // put your main code here, to run repeatedly:

  // todo: react on communication input(s)...
  communication_handler();

  command_handler();

  // todo: do autonomous stuff e.g. dimming, contingency/"idle" mode behaviour...
  // todo: update lighting...
}


//************************
// Communication stuff...
//************************

typedef struct
{
  uint8_t   command;    // commande code...
  uint16_t  light;      // light identifier...
  uint8_t   color[3];   // color rgb data for explicit setting of color...
  uint8_t   intensity;  // intensity value used for showing color...
  uint8_t   pattern;    // pattern...
  uint8_t   palette;    // palette used together with pattern...
  uint16_t  time;       //
}cmd_message_t;

enum
{
  CMD_NONE        = 0,    //
  CMD_STATUS,             //
  CMD_SET_LIGHT,          //
  CMD_ADJ_LIGHT,          //
};

enum
{
  LIGHT_GROUP_NONE    = 0x0000,
  LIGHT_GROUP_FUNNEL  = 0x1000,
  LIGHT_GROUP_STRANDS = 0x2000,
  LIGHT_GROUP_TEXT    = 0x3000,
  LIGHT_GROUP_CIRCLE  = 0x4000,
  LIGHT_GROUP_LIPS    = 0x5000,
  LIGHT_GROUP_EYES    = 0x6000,
  LIGHT_GROUP_BULBS   = 0x7000,
  
  LIGHT_GROUP_ALL     = 0xF000,
};

enum
{
  LIGHT_PATTERN_NONE = 0,
  LIGHT_PATTERN_STATIC,     // used for all but strands!?
  LIGHT_PATTERN_FLICKER,    // only used for strands...
}


QueueList<uint8_t>        g_incoming_buffer;          // queue of bytes before assembly...
QueueList<cmd_message_t>  g_incoming_command_queue;

// todo: init...
void communication_init(void)
{
//  Serial1.begin();
}

//
void communication_handler(void)
{
  static uint8_t buffer_counter = 0;
  static uint8_t buffer[2*sizeof(cmd_message_t)];
  cmd_message_t* ptr = 0;

  // copy to buffer...
  while ((buffer_counter < sizeof(cmd_message_t)) && Serial1.available())
  {
    buffer[buffer_counter] = Serial1.read();
  }

  if (buffer_counter < (sizeof(cmd_message_t) - 1))
  {
    // not a full packet...
    return;
  }

  // todo: sanity check...

  // todo: try to assemble packet..
  // todo: if successful, queue...
  ptr = (cmd_message_t*)buffer;
  g_incoming_command_queue.push(*ptr); // todo: doesn't work...
}


void command_handler(void)
{
  cmd_message_t message;

  message = g_incoming_command_queue.pop(); // todo: doesn't work...

  switch (message.cmd)
  {
    // todo: implement commands...
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
