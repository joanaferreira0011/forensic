#include "generate_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

FILE *logfile = NULL;

int openLogfile() {
    char *logfile_name = getenv("LOGFILENAME");

    logfile = fopen(logfile_name, "a");
    if (logfile == NULL)
    {
        return -1;
    }

    return 0;
}

double get_time() {
    return 0;
}

void updateInfo(char *act)
{
    fprintf(logfile, "%.2f - %.8d - %s\n", get_time(), getpid(), act);
}
