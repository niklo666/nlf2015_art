/*
 * main.cpp
 * shamelessly stolen code...
 * daemonize.c
 * This example daemonizes a process, writes a few log messages,
 * sleeps 20 seconds and terminates afterwards.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <pthread.h>

#include "sync.h"
#include "comm.h"
#include "light.h"
#include "monitor.h"


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

int main()
{
  int err;

    // todo: include the daemon stuff...
    // call the skeletal standard daemon code...
    skeleton_daemon();

    // todo: replace example code...
    // - open config file for settings like start mode etc etc etc...
    //   configs:
    //   camera node ips and ports
    //   camera node algorithm parameters...
    //   light control serial port configs
    // - start new thread and open socket and listen for commands...
    // - start another new thread that:
    // - open serial port and talk to the teensy light controller...
    // - depending on mode connect to configured camera ip/ports...
    // - periodially polls cameras for activity...
    // - starts a third thread that monitors the system e.g. system temp...
    //
    // or startout simpler:
    // - use one main thread that:
    //  * periodically polls the cameras and collect occupancie info...
    //  * call light node to possibly update colors and/or intensities...
    // - use one thread for allowing direct commands from ethernet...

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
  // - periodically poll cameras for info...
  // - update light control as needed...
  //
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
