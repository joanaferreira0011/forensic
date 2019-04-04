#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "path_type.h"
#include "dir_parser.h"
#include "file_parser.h"
#include "wait.h"
#include <sys/types.h>
#include <unistd.h>

int check_dir(char *dir)
{
  struct dirent *de;
  DIR *dr = opendir(dir);
  path_type type;
  char *new_dir = (char *)malloc(60 * sizeof(char));
  type = get_path_type(dir);

  if (type == FILE_PATH)
  {
    parse_file(dir);
    free(new_dir);
    return 0;
  }
  if (dr == NULL)
  {
    printf("Could not open current directory\n");
    free(new_dir);
    return 0;
  }

  else if (type == DIRECTORY)
  {
    parse_file(dir);
    int pid = fork();
    if (pid == 0)
    {
      while ((de = readdir(dr)) != NULL)
      {
        if (strcmp(de->d_name, "..") && strcmp(de->d_name, "."))
        {
          strcpy(new_dir, dir);
          strcat(new_dir, "/");
          strcat(new_dir, de->d_name);
          check_dir(new_dir);
        }
      }
    }
    else if (pid > 0)
    {
      wait(NULL);
    }
  }

  free(new_dir);
  closedir(dr);
  return 0;
}
