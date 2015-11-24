/*
  *** camera_node ***
  comm_protocol.h
*/
// todo: move file/contents to #include "../../shared/camera_protocol.h"

#ifndef COMM_PROTOCOL_H
#define COMM_PROTOCOL_H

enum
{
  CAM_NODE_CMD_MSG_NONE = 0,  //
  CAM_NODE_CMD_MSG_START,     // start camera acquisition...
  CAM_NODE_CMD_MSG_STOP,      // stop camera acquisition...
  CAM_NODE_CMD_MSG_SET_PARAM, // set camera parameter(s)...
  CAM_NODE_CMD_MSG_GET_DATA,  // get camera data...
};

enum
{
  CAM_NODE_RESP_STATUS_OK = 0,

  CAM_NODE_RESP_STATUS_ALREADY_RUNNING,
  CAM_NODE_RESP_STATUS_NOT_RUNNING,

  CAM_NODE_RESP_STATUS_UNKNOWN_PARAMETER,
  CAM_NODE_RESP_STATUS_PARAMETER_OUT_OF_RANGE,
  CAM_NODE_RESP_STATUS_PARAMETER_INVALID,

  CAM_NODE_RESP_STATUS_GENERAL_ERROR = -1,
};

typedef struct
{
  uint8_t cmd;  // command id...
  uint8_t size; // size of payload...
} cam_node_cmd_message_hdr_t;

/*
 response is a cmd hdr with first data object uint8_t containing status i.e. always size >1...
 also inlcude overall system status as we won´t have any async way of alerting system errors for instance low temp, camera fail etc...
*/

#endif // COMM_PROTOCOL_H
