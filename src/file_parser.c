#include<stdio.h>
#include <stdlib.h>
#include "file_parser.h"

void getInfoFile(char file_name[]){
  char info[MAX_STRING_LENGTH];
  char cmd[MAX_STRING_LENGTH];
  //FILE *fp;
  //*fp = FILE *fopen(file_name, r);

  //get file type
  strcpy(cmd, "file");
  strcat(cmd, " ");
  strcat(cmd, file_name);
  system(cmd);
  //



  //int fclose( FILE *fp);
}
