#include <string.h>
#include<stdio.h>
#include "file_parser.h"

int main(int argc, char *argv[ ], char *envp[ ]){
  char file_name[MAX_STRING_LENGTH];
  strcpy(file_name, argv[argc-1]);
  getInfoFile(file_name);
  //printf("%s", getInfoFile(file_name));

}
