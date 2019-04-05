#include "generate_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <sys/times.h>
#include <stdio.h>
#include <time.h>

static bool logging_enabled = false;
static FILE *logfile = NULL;
static clock_t begin;

void write_to_log_COMMAND(int argc, char *argv[])
{
  char info[256];
  strcpy(info, "COMMAND ");

  for (int i = 0; i < argc; i++)
  {
    strcat(info, argv[i]);
    strcat(info, " ");
  }

  while (write_to_log(info))
  {
  }
}

void write_to_log_ANALIZE(char *dir)
{
  char info[256];
  strcpy(info, "ANALIZED ");
  strcat(info, dir);

  while (write_to_log(info))
  {
  };
}

void start_clock()
{
  begin = times(NULL);
}

void close_log_file()
{
  fclose(logfile);
}

int openLogfile(char *logfile_name)
{
  logfile = fopen(logfile_name, "w");
  if (logfile == NULL)
  {
    perror("open_log_file");
    return -1;
  }
  logging_enabled = true;
  return 0;
}

double get_time(clock_t end)
{
  //_SC_CLK_TCK: the number of clock ticks per second.
  double time_spent = (double)(end - begin) / sysconf(_SC_CLK_TCK) * 1000;
  return time_spent;
}

int write_to_log(char *message)
{
  clock_t end = times(NULL);
  double time = get_time(end);

  if (time >= 0)
  {
    if (logging_enabled)
    {
      fprintf(logfile, "%.2f - %.8d - %s\n", time, getpid(), message);
      fflush(logfile);
    }
  }
  return 0;
}
