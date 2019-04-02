#include "generate_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

FILE *log = NULL;

int openLogfile() {
    char *logfile = getenv("LOGFILENAME");

    log = fopen(logfile, "a");
    if (log == NULL)
    {
        return -1;
    }

    return 0;
}

double get_time() {
    
}

void updateInfo(char *act)
{
    fprintf(log, "%.2f - %.8d - %s\n", get_time(), getpid(), act);
}
