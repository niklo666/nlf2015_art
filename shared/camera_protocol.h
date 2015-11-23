/*
  shared include file for definition of the communication between camera and main node...

  use a split command and data channel.
  the command channel is initiated from the main node and support administratiove commands
  the data channel is pure data and possibly no ack (UDP)
*/

typedef struct
{
  uint8_t cmd;      // commande id...
  uint8_t length;   // length of the rest...
}camera_command_comm_header_t;


enum
{
  CAMERA_COMMAND_NONE = 0,      // no command...
  CAMERA_COMMAND_START,         // start, async mode...
  CAMERA_COMMAND_STOP,          // stop, async mode...
  CAMERA_COMMAND_GET_CAM_DATA,  // sync acquire image and perform calculations...
  CAMERA_COMMAND_GET_CAM_IMAGE, // sync acquire image, encode and send...
  CAMERA_COMMAND_STATUS,        // camera node status...
  CAMERA_COMMAND_SET_PARAMETER, // possibility to set new parameters (or always do before start!?)
};

// start command: no parameters
// stop command: no parameters
// status command: no parameters

// set parameter command:
typedef struct
{
  uint8_t parameter_id;
  double  value;
}camera_set_parameters_header_t

// todo: add enum for parameters...
