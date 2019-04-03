#include "generate_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

static bool logging_enabled = false;
static FILE *logfile = NULL;

void close_log_file() {
    fclose(logfile);
}

int openLogfile(char *logfile_name) {
    logfile = fopen(logfile_name, "w");
    if (logfile == NULL) {
        perror("open_log_file");
        return -1;
    }
    logging_enabled = true;
    return 0;
}

double get_time() {
    return 0;
}

void write_to_log(char *message) {
    if (logging_enabled)
        fprintf(logfile, "%.2f - %.8d - %s\n", get_time(), getpid(), message);
}
