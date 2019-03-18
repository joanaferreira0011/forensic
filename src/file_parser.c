#include<stdio.h>
#include <stdlib.h>
#include "file_parser.h"

void getInfoFile(char file_name[]){
  char info[MAX_STRING_LENGTH];
  char cmd[MAX_STRING_LENGTH];

  //get file type
  strcpy(cmd, "file");
  strcat(cmd, " ");
  strcat(cmd, file_name);
  //strcat (cmd, " > output.txt");
  system(cmd);

}
