/*
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

void* command_thread(void*);
void* worker_thread(void*);

int main()
{
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

    while (1)
    {
        //TODO: Insert daemon code here.
        syslog(LOG_NOTICE, "First daemon started.");
        sleep (20);
        break;
    }

    syslog(LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}

// listens for commands through ip socket...
// expose the same interface thru use of the daemon as executable!? possible?
void* command_thread(void* p)
{
  return 0;
}

// periodically polls cameras, handle data and send updates to light controller.
// also waits for commands from the command thread or signals to be killed.
void* worker_thread(void* p)
{
  return 0;
}
