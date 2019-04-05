#include "generate_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

static bool logging_enabled = false;
static FILE *logfile = NULL;
static clock_t begin;

void write_to_log_COMMAND(int argc, char *argv[]){
  char info[256];
  strcpy(info, "COMMAND ");

  for(int i=0; i<argc; i++){
    strcat(info, argv[i]);
    strcat(info, " ");
  }

  while(write_to_log(info)){}
}

void write_to_log_ANALIZE(char * dir){
  char info[256];
  strcpy(info, "ANALIZED ");
  strcat(info, dir);

  while(write_to_log(info)){
  };
}



void start_clock(){
  begin = clock();

}

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
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  return time_spent*100;
}

int write_to_log(char *message) {
  double time = get_time();
  if(time>=0){
    if (logging_enabled){
        fprintf(logfile, "%.2f - %.8d - %s\n",get_time(), getpid(), message);
        fflush(logfile);
    }
  }
  else{
    if (logging_enabled){
        fprintf(logfile, "<0.00 - %.8d - %s\n", getpid(), message);
        fflush(logfile);
    }
  }

    return 0;
}
