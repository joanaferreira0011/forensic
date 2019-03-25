#include <stdio.h>
#include <stdlib.h>
#include "file_parser.h"

char* getFileType(char file_name[])
{
  char str[MAX_STRING_LENGTH];
  char cmd[MAX_STRING_LENGTH];

  //get file type
  strcpy(cmd, "file");
  strcat(cmd, " ");
  strcat(cmd, file_name);
  strcat(cmd, " > output.txt");
  system(cmd);

  FILE *fp;
  fp = fopen("output.txt", "r");

  if (fp == NULL)
  {
    printf("nulo");
  }

  if (fgets(str, MAX_STRING_LENGTH, fp) != NULL)
  {
    memcpy(str, strstr(str, ": ") + 2, strlen(str));
    printf("%s", str);
  }

  fclose(fp);

  return str;
}
