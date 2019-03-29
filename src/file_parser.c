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

FILE *executeCommand (char *file,  char * command) {
  FILE *aux = NULL;
  char cmd[256];
  strcpy(cmd, command);
  strcat(cmd, file);
  aux = popen(cmd, "r");

  return aux;
}


char* getFileType(char *file_name){

  char command[]="file ";
  FILE *type_of_file = executeCommand(file_name, command);
  char aux[256];
  fgets(aux, 255, type_of_file);

  char *file_type = strndup(aux + strlen(file_name) + 2, strlen(aux));

  return file_type;
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
  //getFileMD5(file_name);
  //strcpy(file_info.file_name, file_name);
  strcpy(file_info.file_type,getFileType(file_name));
  if(stat(file_name, &buf)== -1)
    return -1;

  file_info.buf= buf;

  return 0;

}

char* getStringWithInfo(char* file_name){
  char* str;
  str=(char *)malloc(60*sizeof(char));
  char buffer[MAX_STRING_LENGTH];
  getFileInfo(file_name);

  // printf("test: %d\n",file_info.buf.st_uid);

 strcpy(str, file_name);

 strcat(str, ",");
 strcat(str, file_info.file_type);

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
