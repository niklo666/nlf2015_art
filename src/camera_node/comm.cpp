/*
  *** camera_node ***
  comm.c

  todo:
  maybe change comm structure to use one command channel from main node and one data channel to main node.
*/

#include <stdint.h>
#include "comm.h"
#include "../../shared/camera_protocol.h"
//#include "comm_protocol.h"
//#include "sync.h"

/*
void *comm_thread_function( void *ptr )
{
  // todo: create listening thread...

  // loop...
  while (1)
  {
    // todo: wait for connect and handle requests...
  }

  // if we reach here we have either:
  // - unexpectedly "died"/failed...
  // - reacted on a shutdown cmd or so...
  return 0;
}
*/
