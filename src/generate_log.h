#ifndef __GENERATE_LOG_H__
#define __GENERATE_LOG_H__

int openLogfile(char* logfile_name);
void start_clock();
void close_log_file();
int write_to_log(char* act);
void write_to_log_COMMAND(int argc, char *argv[]);
void write_to_log_ANALIZE(char * dir);
#endif/*__GENERATE_LOG_H__*/
