
/*
# import the necessary packages
import argparse
import datetime
import imutils
import time
import cv2

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-v", "--video", help="path to the video file")
ap.add_argument("-a", "--min-area", type=int, default=500, help="minimum area size")
args = vars(ap.parse_args())

# if the video argument is None, then we are reading from webcam
if args.get("video", None) is None:
	camera = cv2.VideoCapture(0)
	time.sleep(0.25)

# otherwise, we are reading from a video file
else:
	camera = cv2.VideoCapture(args["video"])

# initialize the first frame in the video stream
firstFrame = None

# loop over the frames of the video
while True:
	# grab the current frame and initialize the occupied/unoccupied
	# text
	(grabbed, frame) = camera.read()
	text = "Unoccupied"

	# if the frame could not be grabbed, then we have reached the end
	# of the video
	if not grabbed:
		break

	# resize the frame, convert it to grayscale, and blur it
	frame = imutils.resize(frame, width=500)
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	gray = cv2.GaussianBlur(gray, (21, 21), 0)

	# if the first frame is None, initialize it
	if firstFrame is None:
		firstFrame = gray
		continue
    # compute the absolute difference between the current frame and
  	# first frame
  	frameDelta = cv2.absdiff(firstFrame, gray)
  	thresh = cv2.threshold(frameDelta, 25, 255, cv2.THRESH_BINARY)[1]

  	# dilate the thresholded image to fill in holes, then find contours
  	# on thresholded image
  	thresh = cv2.dilate(thresh, None, iterations=2)
  	(cnts, _) = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL,
  		cv2.CHAIN_APPROX_SIMPLE)

  	# loop over the contours
  	for c in cnts:
  		# if the contour is too small, ignore it
  		if cv2.contourArea(c) < args["min_area"]:
  			continue

  		# compute the bounding box for the contour, draw it on the frame,
  		# and update the text
  		(x, y, w, h) = cv2.boundingRect(c)
  		cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
  		text = "Occupied"
*/

#include "opencv2/objdetect.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/videoio/videoio_c.h"
#include "opencv2/highgui/highgui_c.h"

using namespace cv;

int main(int argc, char** argv)
{
  Mat first_frame;
  int got_first_frame = 0;
  VideoCapture cap(0); // open the default camera
  if(!cap.isOpened())  // check if we succeeded
      return -1;

  Mat edges;
  namedWindow("edges",1);
  for(;;)
  {
    int cnt = 0;
      Mat frame, frameDelta, thresh;
      cap >> frame; // get a new frame from camera

//      resize(frame, frame, Size(0,0), 0.5, 0.5);
      cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
      GaussianBlur(edges, edges, Size(21,21), 0);

      if (!got_first_frame)
      {
        first_frame = edges;
        got_first_frame = 1;
      }

      absdiff(first_frame, edges, frameDelta);
    	threshold(frameDelta, thresh, 5, 255, THRESH_BINARY);
      dilate(thresh, thres, NULL, iterations=2)
    	cnt = findContours(thresh, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

      
//      Canny(edges, edges, 0, 30, 3);
      imshow("edges", thresh);
      if(cv::waitKey(30) >= 0) break;
  }


  return 0;
}
