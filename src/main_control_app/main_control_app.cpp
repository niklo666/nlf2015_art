/*
  main_control_app.cpp

  command line application to control the main node as well as connected nodes...
  add a choice to enter interactive mode to run multiple consecutive commands

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
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <syslog.h>
#include <pthread.h>

using namespace std;

void help(void)
{
  cout << "help:\r\n";
  cout << "<app name> <host> <port> light [id] [r],[g],[b] - set light intensity/color (r,g,b) of light source id\r\n";
  cout << "<app name> <host> <port> light [id] 0 - short for light source off\r\n";
  cout << "<app name> <host> <port> light [id] 255 - short for light source full on\r\n";
  cout << "<app name> <host> <port> camera [id] image - acquire, download image and view from camera\r\n";
  cout << "<app name> <host> <port> start   - \r\n";
  cout << "<app name> <host> <port> stop    - \r\n";
  cout << "<app name> <host> <port> status  - \r\n";
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int socket_init(char* hostname, int portno);

int main(int argc, char* argv[])
{
  // todo: parse command line...
  if (argc == 1 || (strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "help") == 0))
  {
    help();
    return 0;
  }
  else if (argc < 4)
  {
    cout << "error: too few arguments...\r\n";
    help();
    return -1;
  }

  if (strcmp(argv[3], "light") == 0)
  {
  }
  else if (strcmp(argv[3], "camera") == 0)
  {
  }

  int sockfd, portno, n;
/*  struct sockaddr_in serv_addr;
  struct hostent *server;*/
  char buffer[256];

  // todo: sanity check...
  portno = atoi(argv[2]);

  sockfd = socket_init(argv[1], portno);
  if (sockfd < 0)
  {
    return -1;
  }

  bzero(buffer,256);

  // todo: implement the actual filling of message contents...

  n = write(sockfd, buffer, strlen(buffer));
  if (n < 0)
  {
    error("ERROR writing to socket");
  }

  bzero(buffer,256);
  n = read(sockfd,buffer,255);
  if (n < 0)
  {
    error("ERROR reading from socket");
  }

  printf("%s\n",buffer);
  close(sockfd);

  return 0;
}

int socket_init(char* hostname, int portno)
{
  int sockfd/*, portno, n*/;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  //char buffer[256];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
  {
    error("ERROR opening socket");
  }

  server = gethostbyname(hostname);
  if (server == NULL)
  {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
  }

  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    error("ERROR connecting");
  }

  return 0;
}
