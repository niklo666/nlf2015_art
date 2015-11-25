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

using namespace cv;


// todo: some kind of "reset" is needed in case parameters are changed...
// or just manually supply a reset command!?
// usually you set up the parameters and then starts acquiring image data and after that never change

static camera_parameters_t  g_parameters;           // todo: init...
static uint8_t              g_parameters_dirty = 1; // used to notify that parameters has been changed...

// todo: does this work...
static cv::VideoCapture      g_video_capture(0);     // open the default camera
static Mat                   g_average_slow;

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

    case CAMERA_PARAMETER_ACCUMULATE_ALPHA_FAST:
      g_parameters.alpha_fast = *value;
      break;

    case CAMERA_PARAMETER_ACCUMULATE_ALPHA_SLOW:
      g_parameters.alpha_slow = *value;
      break;

    case CAMERA_PARAMETER_THRESHOLD:
      g_parameters.threshold = *value;
      break;

    case CAMERA_PARAMETER_THRESHOLD_MAX:
      g_parameters.threshold_max = *value;
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

// sample image and calculate data...
int camera_get_data(camera_data_t* data)
{
  int cnt = 0;
  Mat frame, frameDelta, thresh;
  Mat floatimg;

  // todo: check cap is open...

  cap >> frame; // get a new frame from camera

//      resize(frame, frame, Size(0,0), 0.5, 0.5);
  cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
  GaussianBlur(frame, frame, Size(21,21), 0);

  frame.convertTo(floatimg, CV_32FC3);

  if (first_run)
  {
    cout << "first run";
//        average = Mat::zeros(floatimg.size(), CV_32FC3);
    average = floatimg;
    first_run = 0;
  }

  // # accumulate the weighted average between the current frame and
  // # previous frames, then compute the difference between the current
  // # frame and running average
  // cv2.accumulateWeighted(gray, avg, 0.5)
  //accumulateWeighted(floatimg, average, 0.01);
  accumulateWeighted(floatimg, average_slow, g_parameters.alpha_slow);
  accumulateWeighted(floatimg, average_fast, g_parameters.alpha_fast);

  // frameDelta = cv2.absdiff(gray, cv2.convertScaleAbs(avg))
  absdiff(floatimg, average_slow, frameDelta_slow);
  absdiff(floatimg, average_fast, frameDelta_fast);

  // thresh = cv2.threshold(frameDelta, conf["delta_thresh"], 255, cv2.THRESH_BINARY)[1]
  threshold(frameDelta_slow, thresh_slow, g_parameters.threshold, g_parameters.threshold_max, THRESH_BINARY);
  threshold(frameDelta_fast, thresh_fast, g_parameters.threshold, g_parameters.threshold_max, THRESH_BINARY);

  // thresh = cv2.dilate(thresh, None, iterations=2)
  dilate(thresh_slow, thresh_slow, NULL, Point(-1,-1), 2);
  dilate(thresh_fast, thresh_fast, NULL, Point(-1,-1), 2);

  // (cnts, _) = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
  vector<vector<Point> > contours_slow;
  thresh_slow.convertTo(thresh_slow, CV_8UC1);
  findContours(thresh_slow, contours_slow, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0));

  cout << "Number of contours: " << contours_slow.size() << "\r\n";

  for (int i = 0 ; i < contours.size(); i++)
  {
    // # if the contour is too small, ignore it
		// if cv2.contourArea(c) < args["min_area"]:
		// 	continue

    if (contourArea(contours[i]) >= 100)
    {
      //
  		// # compute the bounding box for the contour, draw it on the frame,
  		// # and update the text
  		// (x, y, w, h) = cv2.boundingRect(c)
      Rect bound = boundingRect(contours[i]);

  		// cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
      rectangle(frame, bound, Scalar(0,0,0));

  		// text = "Occupied"
      String text = "Occupied";

      // # draw the text and timestamp on the frame
    	// cv2.putText(frame, "Room Status: {}".format(text), (10, 20),
      // 	cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)
      //String roomStatus = "Room Status: " << text;
      putText(frame, text, Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 2);

      // cv2.putText(frame, datetime.datetime.now().strftime("%A %d %B %Y %I:%M:%S%p"),
    	// 	(10, frame.shape[0] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (0, 0, 255), 1)
      //
    }
  return 0;
}

int camera_get_image(char** buffer, int* size)
{

  return 0;
}
