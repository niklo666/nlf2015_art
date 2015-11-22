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
void main_thread(void *p);

int main()
{
    // todo: include the daemon stuff...
    // call the skeletal standard daemon code...
//    skeleton_daemon();

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

    while (1)
    {
        //TODO: Insert daemon code here.
        syslog(LOG_NOTICE, "main application started.");
        sleep (20);
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


void main_thread(void *p)
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
