#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "path_type.h"
#include "dir_parser.h"
#include "file_parser.h"
#include "wait.h"
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "generate_log.h"
#include "sighandler.h"

static int pidF;

int check_dir(char *dir, bool recursive, bool outputFile)
{
  struct dirent *de;
  DIR *dr = opendir(dir);
  path_type type;
  char *new_dir = (char *)malloc(60 * sizeof(char));
  type = get_path_type(dir);

  init_signal();
  pidF = getpid();
  enum sig_type msg;

  if (type == FILE_PATH)
  {
    if (outputFile)
    {
      msg = USR2;
      print_signal(msg, pidF);
    }

    parse_file(dir);
    write_to_log_ANALIZE(dir);
    free(new_dir);
    return 0;
  }
  if (dr == NULL)
  {
    printf("Could not open current directory\n");
    free(new_dir);
    return 0;
  }

  else if (type == DIRECTORY && recursive)
  {
    write_to_log_ANALIZE(dir);
    int pid = fork();

    if (outputFile)
    {
      msg = USR1;
      print_signal(msg, pidF);
    }

    if (pid == 0)
    {
      while ((de = readdir(dr)) != NULL)
      {
        if (strcmp(de->d_name, "..") && strcmp(de->d_name, "."))
        {
          strcpy(new_dir, dir);
          strcat(new_dir, "/");
          strcat(new_dir, de->d_name);
          check_dir(new_dir, recursive, outputFile);
        }
      }
      exit(0);
    }
    else if (pid > 0)
    {
      wait(NULL);
    }
  }
  else
  {
    parse_file(dir);
    write_to_log_ANALIZE(dir);
    free(new_dir);
    return 0;
  }

  while (wait(NULL))
  {
    if (errno == EINTR)
      continue;
    else if (errno == ECHILD)
      break;
  }

  free(new_dir);
  closedir(dr);

  return 0;
}
