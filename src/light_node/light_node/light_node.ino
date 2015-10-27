#include <SPI.h>
//#include <mcp_can.h>
//#include <mcp_can_dfs.h>

#include <QueueList.h>

#include <Adafruit_NeoPixel.h>
#include <Adafruit_DotStar.h>


/*

  todo: update light "areas" and behaviours...
  todo: update to handle scenarious and complex workings...
  
  light node
  lighting behaviour needed/wanted:
  - "static" color, used for dna strand, only subject to dimming and possibly "living" colors i.e. glimmering effect using random colors from palette 
  - "static" color, used for strands, possibly more vivid than dna otherwise same or similar
  - "static" colors, used for mouths and eyes, probably only dimming with one static color per item

  communication could be by CAN as it can handle distance and is quite resistant to disturbances *AND* is bidirectional.
  but we will probably go for ttl usart as it is short haul between main controller and light controller
  
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

*/

void setup()
{
  // put your setup code here, to run once:

  // todo: init lighting stuff...
  // - init power control io and see to that power is turned off...
  // - init ws2801 control io and see to that leds are off...
  // - init datastructures...

  // todo: init comm stuff...
  // - use usart 
}

void communication_handler(void);
void command_handler(void);

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
  uint8_t   command;    //
  uint16_t  light;      //
  uint8_t   color[3];   //
  uint8_t   intensity;  //
  uint8_t   pattern;  //
  uint16_t  time;       //
}cmd_message_t;

enum
{
  CMD_NONE    = 0,    //
  CMD_STATUS,         //
  CMD_SET_LIGHT,      //
};


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
  //g_incoming_command_queue.push(*ptr);
  
}

/*
void command_handler(void)
{
  cmd_message_t message;
}
*/

// todo: 



