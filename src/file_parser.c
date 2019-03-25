#include<stdio.h>
#include <stdlib.h>
#include "file_parser.h"
#include <sys/stat.h>



struct file_data{
  struct stat buf;
  char* file_type;
  char* file_name;
};

struct file_data file_info;

void getFileType(char file_name[]){
  char info[MAX_STRING_LENGTH];
  char cmd[MAX_STRING_LENGTH];

  //get file type
  strcpy(cmd, "file");
  strcat(cmd, " ");
  strcat(cmd, file_name);
  strcat (cmd, " > output.txt");
  //system(cmd);

}

void getFileMD5(char file_name[]){
  char info[MAX_STRING_LENGTH];
  char cmd[MAX_STRING_LENGTH];

  //get file type
  strcpy(cmd, "md5sum");
  strcat(cmd, " ");
  strcat(cmd, file_name);
  strcat (cmd, " > output.txt");
  system(cmd);



}


int getFileInfo(char file_name[]){
  struct stat buf;
  getFileMD5(file_name);
  if(stat(file_name, &buf)== -1)
    return -1;

  file_info.buf= buf;

}

char* getStringWithInfo(char file_name[]){
  char str[MAX_STRING_LENGTH];
  char buffer[MAX_STRING_LENGTH];
  getFileInfo(file_name);

  // printf("test: %d\n",file_info.buf.st_uid);

  strcpy(str, file_name);

  //strcat(str, ",");
  // strcat(str, file_data.file_type);

  strcat(str, ",");
  sprintf(buffer, "%lu", file_info.buf.st_size);
  strcat(str, buffer);

  strcat(str, ",");
  sprintf(buffer, "%u", file_info.buf.st_mode);
  strcat(str, buffer);

  strcat(str, ",");
  sprintf(buffer, "%u", file_info.buf.st_mode);
  strcat(str, buffer);

  strcat(str, ",");
  sprintf(buffer, "%lu", file_info.buf.st_atime);
  strcat(str, buffer);

  strcat(str, ",");
  sprintf(buffer, "%lu", file_info.buf.st_mtime);
  strcat(str, buffer);



  printf("%s", str);

  return str;

}
