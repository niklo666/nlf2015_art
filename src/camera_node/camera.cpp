/*
  *** camera_node ***
  camera.c
*/

#include <stdint.h>
#include <inttypes.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/videoio/videoio_c.h"
#include "opencv2/highgui/highgui_c.h"

#include "camera.h"
//#include "sync.h"

// todo: some kind of "reset" is needed in case parameters are changed...
// or just manually supply a reset command!?
// usually you set up the parameters and then starts acquiring image data and after that never change

static camera_parameters_t  g_parameters;           // todo: init...
static uint8_t              g_parameters_dirty = 1; // used to notify that parameters has been changed...

// todo: does this work...
static cv::VideoCapture         g_video_capture(0);     // open the default camera


/*
void *cam_thread_function( void *ptr )
{
}
*/

int camera_init(void)
{
  //g_video_capture = new VideoCapture(0);
  if(!g_video_capture.isOpened())  // check if we succeeded
  {
    return -1;
  }

  // todo: more init stuff!?

  return 0;
}

int camera_set_parameter(uint8_t parameter_id, double value)
{
  switch (parameter_id)
  {
    case CAMERA_PARAMETER_NONE:
      // do nothing...
      break;
  }


  return 0;
}

int camera_get_parameter(uint8_t parameter_id, double *value)
{
  switch (parameter_id)
  {
    case CAMERA_PARAMETER_NONE:
      // do nothing...
      *value = 0.0;
      break;
      
    case CAMERA_PARAMETER_ACCUMULATE_ALPHA_FAST:
    case CAMERA_PARAMETER_ACCUMULATE_ALPHA_SLOW:
    case CAMERA_PARAMETER_THRESHOLD:
    case CAMERA_PARAMETER_THRESHOLD_MAX:
  }

  return 0;
}

int camera_get_data(camera_data_t* data)
{

  return 0;
}

int camera_get_image(char** buffer, int* size)
{

  return 0;
}
