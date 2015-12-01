/*
  *** camera_node ***
  camera.c
*/

#include <iostream>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

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

using namespace cv;
using namespace std;


// todo: some kind of "reset" is needed in case parameters are changed...
// or just manually supply a reset command!?
// usually you set up the parameters and then starts acquiring image data and after that never change

static camera_parameters_t  g_parameters;           // todo: init...
static uint8_t              g_parameters_dirty = 1; // used to notify that parameters has been changed...

// todo: does this work...
static cv::VideoCapture      g_video_capture(0);     // open the default camera
static Mat                   g_average_slow;
static Mat                   g_average_fast;
static int                   g_first_run = 0;

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

int camera_reset(void)
{
  // signal to the frame acquisition routines that a new set of averages shall be maintained...
  g_first_run = 1;
  return 0;
}

int camera_set_parameter(uint8_t parameter_id, double value)
{
  switch (parameter_id)
  {
    case CAMERA_PARAMETER_NONE:
      // do nothing...
      break;

    case CAMERA_PARAMETER_ACCUMULATE_ALPHA_FAST:
      g_parameters.alpha_fast = value;
      break;

    case CAMERA_PARAMETER_ACCUMULATE_ALPHA_SLOW:
      g_parameters.alpha_slow = value;
      break;

    case CAMERA_PARAMETER_THRESHOLD:
      g_parameters.threshold = value;
      break;

    case CAMERA_PARAMETER_THRESHOLD_MAX:
      g_parameters.threshold_max = value;
      break;

    default:
      return CAM_NODE_RESP_STATUS_UNKNOWN_PARAMETER;
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
      *value = g_parameters.alpha_fast;
      break;

    case CAMERA_PARAMETER_ACCUMULATE_ALPHA_SLOW:
      *value = g_parameters.alpha_slow;
      break;

    case CAMERA_PARAMETER_THRESHOLD:
      *value = g_parameters.threshold;
      break;

    case CAMERA_PARAMETER_THRESHOLD_MAX:
      *value = g_parameters.threshold_max;
      break;

    default:
      return CAM_NODE_RESP_STATUS_UNKNOWN_PARAMETER;
  }

  return 0;
}

void my_gettime(struct timespec* ts)
{
#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, ts);
#endif
}

// sample image and calculate data...
// todo: break into sub function to avoid code dups...
// todo: add timing functions to calculate "fps"...
int camera_get_data(camera_data_t* data)
{
  Mat frame;
  Mat frameDelta_slow;
  Mat frameDelta_fast;
  Mat thresh_slow;
  Mat thresh_fast;
  Mat floatimg;
  uint16_t contour_counter_slow = 0;
  uint16_t contour_counter_fast = 0;
  timespec start_time;
  timespec stop_time;

  // get start time...
  my_gettime(&start_time);

  // todo: check cap is open...

  g_video_capture >> frame; // get a new frame from camera

//      resize(frame, frame, Size(0,0), 0.5, 0.5);
  cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
  GaussianBlur(frame, frame, Size(21,21), 0);

  frame.convertTo(floatimg, CV_32FC3);

  if (g_first_run)
  {
    cout << "first run";

//        average = Mat::zeros(floatimg.size(), CV_32FC3);
    g_average_slow = floatimg;
    g_average_fast = floatimg;

    g_first_run = 0;
  }

  // # accumulate the weighted average between the current frame and
  // # previous frames, then compute the difference between the current
  // # frame and running average
  // cv2.accumulateWeighted(gray, avg, 0.5)
  //accumulateWeighted(floatimg, average, 0.01);
  accumulateWeighted(floatimg, g_average_slow, g_parameters.alpha_slow);
  accumulateWeighted(floatimg, g_average_fast, g_parameters.alpha_fast);

  // frameDelta = cv2.absdiff(gray, cv2.convertScaleAbs(avg))
  absdiff(floatimg, g_average_slow, frameDelta_slow);
  absdiff(floatimg, g_average_fast, frameDelta_fast);

  // thresh = cv2.threshold(frameDelta, conf["delta_thresh"], 255, cv2.THRESH_BINARY)[1]
  threshold(frameDelta_slow, thresh_slow, g_parameters.threshold, g_parameters.threshold_max, THRESH_BINARY);
  threshold(frameDelta_fast, thresh_fast, g_parameters.threshold, g_parameters.threshold_max, THRESH_BINARY);

  // thresh = cv2.dilate(thresh, None, iterations=2)
  dilate(thresh_slow, thresh_slow, NULL, Point(-1,-1), 2);
  dilate(thresh_fast, thresh_fast, NULL, Point(-1,-1), 2);

  // (cnts, _) = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
  vector<vector<Point> > contours_slow;
  vector<vector<Point> > contours_fast;
  thresh_slow.convertTo(thresh_slow, CV_8UC1);
  thresh_fast.convertTo(thresh_fast, CV_8UC1);
  findContours(thresh_slow, contours_slow, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));
  findContours(thresh_fast, contours_fast, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

  cout << "Number of slow contours: " << contours_slow.size() << "\r\n";
  cout << "Number of fast contours: " << contours_fast.size() << "\r\n";

  // todo: add option to make processed and/or raw images available...

  int i = 0;
  for (i = 0 ; i < contours_slow.size(); i++)
  {
    if (contourArea(contours_slow[i]) >= 100)
    {
      // todo: implement slots...
      // idea: use bounding rects to get this...
      // see example code for achieving this...

      // count contours...
      contour_counter_slow++;
    }
  }

  for (i = 0 ; i < contours_fast.size(); i++)
  {
    if (contourArea(contours_fast[i]) >= 100)
    {
      // todo: implement slots or ignore for fast movement!?
      contour_counter_fast++;
    }
  }

  // for now use a single slot...
  data->slot_count_slow[0] = contour_counter_slow;
  data->slot_count_slow[0] = contour_counter_fast;

  // get stop time...
  // get start time...
  my_gettime(&stop_time);

  // todo: calculate time diff...

  return 0;
}

int camera_get_image(char** buffer, int* size)
{

  return 0;
}
