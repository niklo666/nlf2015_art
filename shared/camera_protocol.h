/*
  shared include file for definition of the communication between camera and main node...

  use a split command and data channel.
  the command channel is initiated from the main node and support administratiove commands
  the data channel is pure data and possibly no ack (UDP)
*/

#ifndef CAMERA_PROTOCOL_H
#define CAMERA_PROTOCOL_H

#define CAMERA_NODE_PROTOCOL_VERSION 0x0001 //

#define CAMERA_NODE_DEFAULT_PORT  1347

#define CAMERA_NODE_MAX_NUMBER_OF_SLOTS 10

typedef struct
{
  uint8_t cmd;      // command id...
  uint8_t size;     // length of the rest...
}camera_command_comm_header_t;

typedef struct
{
  uint8_t cmd;      // command id...
  uint8_t status;   //
  uint8_t size;     // length of the rest...
}camera_response_header_t;

enum
{
  CAMERA_COMMAND_NONE = 0,      // no command...
//  CAMERA_COMMAND_START,         // reserved: start, async mode...
//  CAMERA_COMMAND_STOP,          // reserved: stop, async mode...
  CAMERA_COMMAND_GET_CAM_DATA,  // sync acquire image and perform calculations...
  CAMERA_COMMAND_GET_CAM_IMAGE, // sync acquire image, encode and send...
  CAMERA_COMMAND_STATUS,        // camera node status...
  CAMERA_COMMAND_SET_PARAMETER, // possibility to set new parameters (or always do before start!?)
  CAMERA_COMMAND_GET_PARAMETER, // possibility to set new parameters (or always do before start!?)
};

enum
{
  CAM_NODE_RESP_STATUS_OK = 0,

  CAM_NODE_RESP_STATUS_UNKNOWN_COMMAND,

//  CAM_NODE_RESP_STATUS_ALREADY_RUNNING,
//  CAM_NODE_RESP_STATUS_NOT_RUNNING,

  CAM_NODE_RESP_STATUS_UNKNOWN_PARAMETER,
  CAM_NODE_RESP_STATUS_PARAMETER_OUT_OF_RANGE,
  CAM_NODE_RESP_STATUS_PARAMETER_INVALID,

  CAM_NODE_RESP_STATUS_GENERAL_ERROR = -1,
};

enum
{
  CAMERA_PARAMETER_NONE = 0,

  // averaging...
  CAMERA_PARAMETER_ACCUMULATE_ALPHA_FAST, // fast adapting to react on movement...
  CAMERA_PARAMETER_ACCUMULATE_ALPHA_SLOW, // slow adapting to react on non-moving occupancy...

  // threshold...
  CAMERA_PARAMETER_THRESHOLD,
  CAMERA_PARAMETER_THRESHOLD_MAX,

  // contours...
  CAMERA_PARAMETER_MIN_CONTOUR_AREA,

  //...
};


typedef struct
{
  uint8_t number_of_slots;                                    // good to know even if static!?
  uint8_t slot_count_slow[CAMERA_NODE_MAX_NUMBER_OF_SLOTS];   //
  uint8_t slot_count_fast[CAMERA_NODE_MAX_NUMBER_OF_SLOTS];   //
  uint16_t execution_time_ms;                                // execution time for image processing...
}camera_data_t;


// start command: no parameters
// stop command: no parameters
// status command: no parameters

// set parameter command:
typedef struct
{
  uint8_t parameter_id;
  double  value;
}camera_set_parameters_header_t;


// todo: add enum for parameters...

#endif // CAMERA_PROTOCOL_H
