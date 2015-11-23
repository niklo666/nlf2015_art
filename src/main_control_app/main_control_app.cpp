/*
  main_control_app.cpp

  command line application to control the main node as well as connected nodes...

  example:
  <app> light n r g b - set color/intensity (r,g,b) of light source n
  <app> camera n image  - get image from camera node n
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <pthread.h>

using namespace std;

void help(void)
{
  cout << "help:\r\n";
  cout << "<app name> light [id] [r],[g],[b] - set light intensity/color (r,g,b) of light source id\r\n";
  cout << "<app name> light [id] 0 - short for light source off\r\n";
  cout << "<app name> light [id] 255 - short for light source full on\r\n";
  cout << "<app name> camera [id] image - acquire, download image and view from camera\r\n";
  cout << "<app name> start   - \r\n";
  cout << "<app name> stop    - \r\n";
  cout << "<app name> status  - \r\n";
}

int main(int argc, char* argv[])
{
  // todo: parse command line...
  if (argc == 1)
  {
    help();
    return -1;
  }

  if (strcmp(argv[1], "light") == 0)
  {
  }
  else if (strcmp(argv[1], "camera") == 0)
  {
  }


  return 0;
}
