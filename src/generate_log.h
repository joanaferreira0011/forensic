#ifndef __GENERATE_LOG_H__
#define __GENERATE_LOG_H__

#include <stdio.h>
#include <time.h>

int openLogfile(char* logfile_name);
void start_clock();
void close_log_file();
int write_to_log(char* act, clock_t end);
void write_to_log_COMMAND(int argc, char *argv[]);
void write_to_log_ANALIZE(char * dir, clock_t end);
#endif/*__GENERATE_LOG_H__*/
