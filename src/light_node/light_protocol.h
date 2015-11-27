/*
  shared include file for definition of the communication between light and main node...

  this is the real deal! the non-arduino code use the wrapper include file in
  "shared" folder for symmetry.
*/

#ifndef LIGHT_PROTOCOL_H
#define LIGHT_PROTOCOL_H

//************************
// Communication stuff...
//************************

typedef struct
{
  uint8_t   start_magic;// start magic...
  uint8_t   command;    // commande code...
  uint16_t  light;      // light identifier...
  uint8_t   color[3];   // color rgb data for explicit setting of color...
  uint8_t   intensity;  // intensity value used for showing color...
  uint8_t   pattern;    // pattern...
  uint8_t   palette;    // palette used together with pattern...
  uint16_t  time;       //
  uint8_t   stop_magic; // stop magic...
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

#endif // LIGHT_PROTOCOL_H
