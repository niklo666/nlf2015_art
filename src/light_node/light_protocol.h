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

const uint8_t LIGHT_NODE_MESSAGE_START_MAGIC  = 0x02;
const uint8_t LIGHT_NODE_MESSAGE_STOP_MAGIC   = 0x03;

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
}light_node_cmd_message_t;

typedef struct
{
  uint8_t   start_magic;  // start magic...
  uint8_t   command;      // for matching and sanity...
  uint8_t   status;       // the actual response....
  uint8_t   stop_magic;   // stop magic...
}light_node_resp_message_t;

enum
{
  LIGHT_NODE_STATUS_OK,  //

  LIGHT_NODE_STATUS_UNKNOWN_COMMAND,

  LIGHT_NODE_STATUS_GENERAL_ERROR = 0xff
};

enum
{
  LIGHT_NODE_COMMAND_NONE        = 0,    // no real action here...
  LIGHT_NODE_COMMAND_STATUS,             // return unit status...
  LIGHT_NODE_COMMAND_SET_LIGHT,          //
  LIGHT_NODE_COMMAND_ADJ_LIGHT,          //
  LIGHT_NODE_COMMAND_LIGHT_OFF,          //
};

enum
{
  LIGHT_GROUP_NONE    = 0,
  LIGHT_GROUP_STRANDS = 1,
  LIGHT_GROUP_LIPS    = 2,
  LIGHT_GROUP_EYES    = 3,
  LIGHT_GROUP_TEXT0   = 4,
  LIGHT_GROUP_TEXT1   = 5,
  LIGHT_GROUP_BULBS   = 6,

  LIGHT_GROUP_ALL     = 0xff,
};

enum
{
  LIGHT_PATTERN_NONE = 0,
  LIGHT_PATTERN_STATIC,     // used for all but strands!?
  LIGHT_PATTERN_FLICKER,    // only used for strands...
}

#endif // LIGHT_PROTOCOL_H
