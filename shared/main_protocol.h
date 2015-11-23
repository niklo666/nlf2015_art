/*
  shared include file for definition of the communication with the main node...
*/

//
#include <stdint.h>
#include <inttypes.h>

#ifndef MAIN_PROTOCOL_H
#define MAIN_PROTOCOL_H

typedef struct
{
  uint8_t cmd;      // commande id...
  uint8_t length;   // length of the rest...
}main_command_comm_header_t;

enum
{
  MAIN_COMMAND_NONE = 0,              // no command...
  MAIN_COMMAND_START,                 // start cyclic execution...
  MAIN_COMMAND_STOP,                  // stop cyclic execution...
  MAIN_COMMAND_STATUS,                // query main node status...

  // camera commands...
  MAIN_COMMAND_GET_CAMERA_PARAMETER,  // possibility to set new parameters (or always do before start!?)
  MAIN_COMMAND_SET_CAMERA_PARAMETER,  // possibility to set new parameters (or always do before start!?)

  // light node commands...
  MAIN_COMMAND_LIGHT_CONTROL,
};

// start command...
// no parameters
// response: header...

// stop command...
// no parameters
// response: header...

// status command...
// no parameters
// response: header + unsigned integer...

// light control...
// parameters:
// - light source
// - color/intensity...
// -...

#endif // MAIN_PROTOCOL_H