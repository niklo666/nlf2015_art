/*
  *** camera_node ***
  main.cpp

  todo: first throw: regular app, synchronous acquiring of images...
  todo: implement get image commands/functions to test on site e.g. get the idea of good sectors, use opencv imencode...

  functionality:
  - comm thread: open socket and listen for requests (start, stop, get data, set parameters) in own thread...
  - cam thread: separate thread for acquiring cam images and perform calculations...

*/

// todo: daemonize!!!
// todo: implement syslogging...
// todo: s-i-m-p-l-i-f-y!!! all synchronous
// basically:
// - init socket and listen for requests...
// - on accept listen for commands that are synchronously executed...
// simple commands:
// - set/get params...
// - acquire calculated image data...
// - acquire raw (encoded) image data...
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "comm.h"
#include "camera.h"
#include "monitor.h"

int main()
{
  int ret = 0;

  pthread_t comm_thread;
  pthread_t camera_thread;
  pthread_t monitor_thread;

  // todo: create/init data queue...
  // todo: create start/stop sync item(s), init to stop...



  // create/start cam thread...
  ret = pthread_create(camera_thread, NULL, cam_thread_function, NULL);
  if (ret)
  {
    // error: failed to create thread...
    // todo: log and die!
    return -1;
  }

  // todo: create/start monitoring thread, monitor "system" e.g. measure temperature...
  ret = pthread_create(monitor_thread, NULL, comm_thread_function, NULL);
  if (ret)
  {
    // error: failed to create thread...
    // todo: log and die!
    return -1;
  }

  // create/start comm thread...
  ret = pthread_create(comm_thread, NULL, comm_thread_function, NULL);
  if (ret)
  {
    // error: failed to create thread...
    // todo: log and die!
    return -1;
  }

  // wait for threads to die...
  pthread_join(camera_thread, NULL);

  // camera thread has died...
  // if comm thread is still running tell it somehow...

  pthread_join(comm_thread, NULL);

  // if we reach here both of the threads has died...
  // probably it should be like that but...

  return 0;
}
