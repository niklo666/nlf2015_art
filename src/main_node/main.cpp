/*
 * main.cpp
 * shamelessly stolen code...
 * daemonize.c
 * This example daemonizes a process, writes a few log messages,
 * sleeps 20 seconds and terminates afterwards.
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <pthread.h>


//#include "sync.h"
#include "comm.h"
#include "light.h"
//#include "monitor.h"
#include "config.h"

using namespace std;

//
pthread_t main_tid = 0;
pthread_t comm_tid = 0;

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
    openlog("rpi_main_controller", LOG_PID, LOG_DAEMON);
}

// the main thread to perform all or most stuff in the simple implementation.
// could easily be moved to separate  etc...
void* main_thread(void *p);

void signal_handler(int signo);

int g_cam1_socket = -1;
int g_cam2_socket = -1;
int g_cam3_socket = -1;

int main_connect_to_cameras(void);
int main_load_configuration(char* config_file);
int main_config_cameras(void);

int main(int argc, char* argv[])
{
  int err;
  int ret;

    // todo: include the daemon stuff...
    // call the skeletal standard daemon code...
    //skeleton_daemon();

    // todo: replace example code...
    // - open config file for settings like start mode etc etc etc...
    //   configs:
    //   camera node ips and ports
    //   camera node algorithm parameters...
    //   light control serial port configs
    // - start new thread and open socket and listen for commands...
    // - start another new thread that:
    // - open serial port and talk to the teensy light controller...
    // - depending on mode conn ect to configured camera ip/ports...
    // - periodially polls cameras for activity...
    // - starts a third thread that monitors the system e.g. system temp...
    //
    // or startout simpler:
    // - use one main thread that:
    //  * periodically polls the cameras and collect occupancie info...
    //  * call light node to possibly update colors and/or intensities...
    // - use one thread for allowing direct commands from ethernet...

    //************************
    // the simple solution...
    //************************

    // init syslog...
    openlog("main_node", LOG_PID, LOG_DAEMON);

    // load configurations...
    ret = main_load_configuration(argv[1]);
    if (ret)
    {
      return ret;
    }

    // todo: turn on power to the camera nodes or do from script!?
    // or maybe camera nodes and/or camera node apps are started/controlled by script!?

    // todo: connect to the camera nodes...
    ret = main_connect_to_cameras();
    if (ret)
    {
      return ret;
    }

    // todo: config the camera nodes...
    // - get all config parameters...
    // - send them to the nodes...
    ret = main_config_cameras();
    if (ret)
    {
      return ret;
    }

    // todo: open serial port to light controller and check connection...
    ret = main_open_light_node_serial_port("/dev/ttyAMA0");
    if (ret)
    {
      return ret;
    }

    // todo: check light node status...


    // enter application loop...
    while (1)
    {
      // todo:
      // - once a second poll all cameras for data...
      // - convert the occupancy data to light behaviour...
      // e.g. accumulate diff in occupancy to control dim levels and enter modes...
      // - send updates to the light node...

      // todo: need to break down behaviour:
      // intro  - run a "show" as startup
      // normal - react on movement/occupancy up to a certain level by dim up of lights (strands and globes)...
      // ilwt   - at a certain threshold (movement/occupancy or time) enter a mode where_
      //   * the lips are dimmed up
      //   * the text is lit/flashed...
      //   * globes are dimmed down to accentuate...
      // voyeur - on movement on the rear dim up the eyes...
      // outro  - run a "show" at closing down...

     }



/*
    // todo: get configurations...

    // todo: no loop when using threads....
    while (1)
    {
        //TODO: Insert daemon code here.
        syslog(LOG_NOTICE, "main application started.");

        // todo: start main thread...
        err = pthread_create(&main_tid, NULL, &main_thread, NULL);
        if (err != 0)
            {
              // todo: handle error...
              //printf("\ncan't create thread :[%s]", strerror(err));
              printf("\ncan't create thread :[%d]", err);
            }
        else
            {
              printf("\n Thread created successfully\n");
            }

        // todo: start comm thread...
        err = pthread_create(&comm_tid, NULL, &main_thread, NULL);
        if (err != 0)
            {
              // todo: handle error...
              //printf("\ncan't create thread :[%s]", strerror(err));
              printf("\ncan't create thread :[%d]", err);
            }
        else
            {
              printf("\n Thread created successfully\n");
            }

        // todo: join on threads or at least check why we're here...

        break;
    }

    syslog(LOG_NOTICE, "main application terminated.");
    closelog();

    return EXIT_SUCCESS;
*/
}

enum
{
  RUN_MODE_IDLE = 0,  // idle looping waiting for commands...
  RUN_MODE_NORMAL,    // running the normal control looop...
};


void* main_thread(void *p)
{
  // todo: implement...
  // - init:
  //  * load configuration or use default parameters...
  //  * init cameras...
  //  * open serial port to light controller
  //  * init light controller...

  while (1)
  {
    // todo:
    // - periodically poll cameras for info...
    // - update light control as needed...
  }

  // if we reach here something has gone terribly wrong or we're requested to exit...
}

void signal_handler(int signo)
{
  switch (signo)
  {
    case SIGINT:
      printf("received SIGINT\n");
      break;

    case SIGCHLD:
      printf("received SIGCHLD\n");
      break;

    case SIGHUP:
      printf("received SIGHUP\n");
      break;

    case SIGTERM:
      // generated by 'kill'...
      printf("received SIGTERM\n");
      break;

    case SIGKILL:
      // can not be handled...
      printf("received SIGKILL\n");
      break;

    case SIGSTOP:
      printf("received SIGSTOP\n");
      break;

    default:
      printf("unhandled signal: %d\n", signo);
      break;

  }

}


int main_connect_to_cameras(void)
{
  char cam1_ip[16];
  char cam2_ip[16];
  char cam3_ip[16];
  int cam1_port;
  int cam2_port;
  int cam3_port;

  config_get_string_value("cam1_ip", cam1_ip);
  config_get_string_value("cam2_ip", cam2_ip);
  config_get_string_value("cam3_ip", cam3_ip);
  config_get_int_value("cam1_port", &cam1_port);
  config_get_int_value("cam2_port", &cam2_port);
  config_get_int_value("cam3_port", &cam3_port);

  g_cam1_socket = comm_connect(cam1_ip, cam1_port);
  if (cam1_socket == -1)
  {
    cerr << "error: failed to connect to camera 1\n";
    return -1;
  }

  g_cam2_socket = comm_connect(cam2_ip, cam2_port);
  if (cam2_socket == -1)
  {
    cerr << "error: failed to connect to camera 2\n";
    return -1;
  }

  g_cam3_socket = comm_connect(cam3_ip, cam3_port);
  if (cam3_socket == -1)
  {
    cerr << "error: failed to connect to camera 3\n";
    return -1;
  }

  return 0;
}

int main_load_configuration(char* config_file)
{
  int ret;

  if (config_file != NULL)
  {
    ret = config_read(config_file);
  }
  else
  {
    // default config file...
    ret = config_read("config.txt");
  }

  if (ret)
  {
    cerr << "error: failed to read config. exiting...";
    return -1;
  }

  return 0;
}

int main_config_cameras(void)
{
  int ret;

  // todo: get all configuration parameters...
  // todo: send all configurations...

  return 0;
}
