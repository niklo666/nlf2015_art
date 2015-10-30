/*
  *** camera_node ***
  sync.c
*/

#include "sync.h"


typedef struct
{
    // todo: add parameters...

}parameters_t;

typedef struct
{
    // todo: add data...

    // camera data...
    // - sync object...
    // - number of detected objects per slot/sector...
    // - area of detected objects...
    // - error codes...

    // system data...
    // - sync object...
    // - system temperature...

}data_t;

static volatile uint8_t g_cam_thread_order;     // used to start or stop (or exit?) camera thread...
static volatile uint8_t g_cam_thread_status;    // used to feedback cam thread status...


void set_camera_order(uint8_t order)
{
  g_cam_thread_order = order;
}

uint8_t get_camera_order(void)
{
  return g_cam_thread_order;
}

void set_camera_status(uint8_t status)
{
  g_cam_thread_status = status;
}

uint8_t get_camera_status(void)
{
  return g_cam_thread_status;
}
