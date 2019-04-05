#include "sighandler.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static int directories = 0;
static int files = 0;

void handler(int signo)
{
    if (signo == SIGUSR1)
    {
        directories++;
        printf("New directory: %d/%d directories/files at this time.\n", directories, files);
    }
    else if (signo == SIGUSR2)
    {
        files++;
    }
}

int init_signal()
{
    struct sigaction action;

    // prepare the 'sigaction struct' 
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    
    // install the handler 
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    return 0;
}

int print_signal(enum sig_type msg, int pid)
{
    switch (msg)
    {
    case 0:
        if (kill(pid, SIGUSR1))
        {
            return 1;
        }
        break;

    case 1:
        if (kill(pid, SIGUSR2))
        {
            return 1;
        }
        break;
    }

    return 0;
}