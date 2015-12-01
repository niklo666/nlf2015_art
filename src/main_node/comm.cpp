/*
  *** main_node ***
  comm.cpp

  comm thread...
  listens for incoming control commands.
  used to:
  - start/stop automatic control mode(s)...
  - direct control of lights (either aborting auto modes or demanding stopping it first)...
  - status inquiries...
*/

#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>

//#include "../../shared/camera_protocol.h"
#include "../../shared/camera_protocol.h"
#include "comm.h"

void* comm_thread_function(void* ptr)
{

  return 0;
}
