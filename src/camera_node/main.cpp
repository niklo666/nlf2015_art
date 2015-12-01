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

#include <iostream>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "comm.h"
#include "camera.h"
#include "monitor.h"
#include "../../shared/camera_protocol.h"

using namespace std;

/*
int set_parameter_handler(uint8_t parameter, double value);
int get_parameter_handler(uint8_t parameter, double &value);
int get_derived_image_data_handler();
int get_raw_image_data_handler();
*/

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// TODO: implement signal handlers...
void sig_handler(int signum)
{
    printf("Received signal %d\n", signum);
}


static void skeleton_daemon()
{
    pid_t pid;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0)
    {
      exit(EXIT_FAILURE);
    }


    /* Success: Let the parent terminate */
    if (pid > 0)
    {
      exit(EXIT_SUCCESS);
    }


    /* On success: The child process becomes session leader */
    if (setsid() < 0)
    {
      exit(EXIT_FAILURE);
    }


    /* Catch, ignore and handle signals */
    //TODO: Implement a working signal handler */
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    /* Fork off for the second time*/
    pid = fork();

    /* An error occurred */
    if (pid < 0)
    {
      exit(EXIT_FAILURE);
    }

    /* Success: Let the parent terminate */
    if (pid > 0)
    {
      exit(EXIT_SUCCESS);
    }

    /* Set new file permissions */
    umask(0);

    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    chdir("/");

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog("rpi_camera_node", LOG_PID, LOG_DAEMON);
}

int client_handler(int sockfd, struct sockaddr_in* cli_addr);
int command_handler(int sockfd);

int main(int argc, char* argv[])
{
  int sockfd, newsockfd, portno;
   socklen_t clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int n;
   int ret = 0;

  // todo: daemon stuff...
//  skeleton_daemon();

  // todo: init stuff e.g. socket...

   if (argc == 2)
   {
     portno = atoi(argv[1]);
   }
   else
   {
     cout << "WARNING: default camera node port is used\r\n";
     portno = CAMERA_NODE_DEFAULT_PORT;
   }


   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
    {
      error("ERROR opening socket");
    }

  cout << "Successfully created socket\r\n";

   bzero((char *) &serv_addr, sizeof(serv_addr));

   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
      error("ERROR on binding");
    }

  cout << "Successful bind to port number: " << portno << "\r\n";
  cout << "Listening...\r\n";

  listen(sockfd, 5);

  while (1)
  {
    // handle incoming client requests...
    newsockfd = client_handler(sockfd, &cli_addr);
    if (newsockfd < 0)
    {
      // todo: handle error...
      continue;
    }

    while (1)
    {
      // handle incoming commands...
      // no reason to support more than one client at the moment...
      ret = command_handler(newsockfd);
      if (ret != 0)
      {
        // todo: handle any errors...
        // decide what to do:
        // - log/print...
        // - restart/die/whatever...
        break;
      }
    }
  }

  // if we end up here it´s the end for the application!!!
  return 0;
}


int client_handler(int sockfd, struct sockaddr_in* cli_addr)
{
  int newsockfd;
  socklen_t clilen;

  // todo: accept connects...
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

  if (newsockfd < 0)
  {
    error("ERROR on accept");

    // todo: log error!?
    // todo: handle error...
  }

  cout << "client accepted\r\n";

  return newsockfd;
}

int command_handler(int newsockfd)
{

  int ret;
  char buffer[256];
  int n;
  camera_set_parameters_header_t* param_hdr;
  camera_data_t* data;

  // todo: wait for and process commands...
  bzero(buffer, 256);
  n = read(newsockfd, buffer, 255);
  if (n < 0)
  {
    error("ERROR reading from socket");
    // todo: log error!?
    // todo: handle error...
  }

  // todo: check that we have enough to make a command!

  // process the command...
  camera_command_comm_header_t* hdr = (camera_command_comm_header_t*)buffer;
  camera_response_header_t* resp = (camera_response_header_t*)buffer;

  switch (hdr->cmd)
  {
    case CAMERA_COMMAND_NONE:
      // do nothing...
      resp->status = CAM_NODE_RESP_STATUS_OK;
      resp->size = 0;
      break;

    case CAMERA_COMMAND_GET_CAM_DATA:
      // todo: implement...
      // todo: test...

      // get the camera_data_t header
      // todo: sanity check and does the header fit in the data received!?
      data = (camera_data_t*)(buffer + sizeof(camera_command_comm_header_t));
      ret = camera_get_data(data);
      resp->status = ret;
      if (ret == CAM_NODE_RESP_STATUS_OK)
      {
        resp->size = sizeof(camera_data_t);
      }
      else
      {
        resp->size = 0;
      }
      break;

    case CAMERA_COMMAND_GET_CAM_IMAGE:
      // todo: implement...
      break;

    case CAMERA_COMMAND_STATUS:
      // todo: implement...
      break;

    case CAMERA_COMMAND_SET_PARAMETER:
      // todo: implement...
      // todo: test...
      param_hdr = (camera_set_parameters_header_t*)(buffer + sizeof(camera_command_comm_header_t));
      ret = camera_set_parameter(param_hdr->parameter_id, param_hdr->value);
      resp->status = ret;
      resp->size = 0;
      break;

    case CAMERA_COMMAND_GET_PARAMETER:
      // todo: implement...
      // todo: test...
      param_hdr = (camera_set_parameters_header_t*)&buffer[sizeof(camera_command_comm_header_t)];
      ret = camera_get_parameter(param_hdr->parameter_id, &(param_hdr->value));
      resp->status = ret;
      if (ret == CAM_NODE_RESP_STATUS_OK)
      {
        resp->size = sizeof(camera_set_parameters_header_t);
      }
      else
      {
        resp->size = 0;
      }
      break;

    default:
      // todo: handle unknown command...
      resp->status = CAM_NODE_RESP_STATUS_UNKNOWN_COMMAND;
      resp->size = 0;
      break;
  }

  // todo: send response...
  n = write(newsockfd, buffer, sizeof(camera_response_header_t) + resp->size);
  if (n < 0)
  {
    error("ERROR writing to socket");
    // todo: handle error...
  }

  return 0;
}
