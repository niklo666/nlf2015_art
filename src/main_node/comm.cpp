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

#include <iostream>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//#include "../../shared/camera_protocol.h"
#include "../../shared/camera_protocol.h"
#include "comm.h"
#include "config.h"

using namespace std;


/*
void* comm_thread_function(void* ptr)
{

  return 0;
}
*/

int comm_connect(char* hostname, int portno)
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;


    //  create socket...
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
      cerr << "ERROR opening socket\n";
      return -1;
    }

    server = gethostbyname(hostname);
    if (server == NULL)
    {
        cerr << "ERROR, no such host\n";
        return -1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
      cerr << "ERROR connecting\n";
      return -1;
    }

    return sockfd;
}

int comm_send_command(int sockfd, camera_command_comm_header_t* hdr, void* payload, void* resp_payload)
{
  int i;
  char buffer[256];
  int buffer_counter = 0;
  char* data_ptr = NULL;

  // copy to buffer...
  data_ptr = (char*)hdr;
  for (i=0; i<sizeof(camera_command_comm_header_t); i++)
  {
    buffer[buffer_counter++] = *data_ptr;
    data_ptr++;
  }

  data_ptr = (char*)payload;
  for (i=0; i<sizeof(hdr->size); i++)
  {
    buffer[buffer_counter++] = *data_ptr;
    data_ptr++;
  }

  // ready to send it off...
  int n = write(sockfd, buffer, buffer_counter);
  if (n < 0)
  {
    cerr << "ERROR writing to socket";
    return -1;
  }

  // get the response...
  bzero(buffer, 256);
  n = read(sockfd, buffer, sizeof(camera_response_header_t));
  if (n < 0)
  {
    cerr << "ERROR reading from socket";
    return -1;
  }

  camera_response_header_t* resp = (camera_response_header_t*)buffer;
  if (resp->status != CAM_NODE_RESP_STATUS_OK)
  {
    cerr << "error command failed: " << resp->status << "\n";
    return -1;
  }

  if (resp->size)
  {
    bzero(buffer, 256);
    n = read(sockfd, buffer, resp->size);
    if (n < 0)
    {
      cerr << "ERROR reading from socket";
      return -1;
    }
  }

  // copy to response payload...
  if (resp_payload != NULL)
  {
    data_ptr = (char*)resp_payload;
    for (i=0; i < resp->size; i++)
    {
      *data_ptr = buffer[i];
      data_ptr++;
    }
  }

  return 0;
}


int comm_set_camera_parameter(int socket, int parameter, double value)
{
  camera_command_comm_header_t hdr;
  camera_set_parameters_header_t param;

  // fill header...
  hdr.cmd = CAMERA_COMMAND_SET_PARAMETER;
  hdr.size = sizeof(param);

  // fill param...
  param.parameter_id = parameter;
  param.value = value;

  int ret;

  ret = comm_send_command(socket, &hdr, (void*)&param, NULL);

  return ret;
}

int comm_get_camera_data(camera_data_t* camera_data)
{
    return 0;
}
