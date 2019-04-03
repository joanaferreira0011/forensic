#include <stdio.h>
#include <stdlib.h>
#include "file_parser.h"
#include <sys/stat.h>
#include <time.h>

static FILE *output_file = NULL;
static hash_options_t hash_options = {
  .md5 = false,
  .sha1 = false,
  .sha256 = false
};

void set_output_to_stdout() {
  output_file = stdout;
}

void set_hash_options(hash_options_t new_options) {
  hash_options = new_options;
}

void close_output_file() {
  fclose(output_file);
}

int set_external_output_file(char *path_to_output_file) {
  FILE *new_output_file = fopen(path_to_output_file,"w");
  if (new_output_file == NULL) {
    perror("set_external_output_file");
    return -1;
  }
  output_file = new_output_file;
  atexit(close_output_file);
  printf("set output file to %s\n",path_to_output_file);
  return 0;
}

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

  char *pos;
  if ((pos=strchr(file_type, '\n')) != NULL)
    *pos = '\0';

  fclose(type_of_file);
  return file_type;
}

char* getMD5(char *file_name){
  char command[] = "md5sum ";
  FILE *md5sum = executeCommand(file_name, command);
  char aux[256];
  fgets(aux, 255, md5sum);

  char *md5 = strndup(aux , strlen(aux) - strlen(file_name) - 3);

  char *pos;
  if ((pos=strchr(md5, '\n')) != NULL)
    *pos = '\0';

  fclose(md5sum);
  return md5;
}

char* getSha1Sum (char *file_name){
  char command[] = "sha1sum ";
  FILE *sha1sum = executeCommand(file_name, command);
  char aux[256];
  fgets(aux, 255, sha1sum);

  char *sha1 = strndup(aux , strlen(aux) - strlen(file_name) - 3);

  char *pos;
  if ((pos=strchr(sha1, '\n')) != NULL)
    *pos = '\0';

  fclose(sha1sum);
  return sha1;
}

char* getSha256Sum (char *file_name){
  char command[] = "sha256sum ";
  FILE *sha256sum = executeCommand(file_name, command);
  char aux[256];
  fgets(aux, 255, sha256sum);

  char *sha256 = strndup(aux , strlen(aux) - strlen(file_name) - 3);

  char *pos;
  if ((pos=strchr(sha256, '\n')) != NULL)
    *pos = '\0';

  fclose(sha256sum);
  return sha256;
}

int getFileInfo(char file_name[], file_info *info){
  struct stat buf;
  char buffer[MAX_STRING_LENGTH];
  char aux[MAX_STRING_LENGTH];
  char str[MAX_STRING_LENGTH];
  char bufs[MAX_STRING_LENGTH];

  if(stat(file_name, &buf)== -1)
    return -1;

  //FILE NAME
  info->file_name = file_name;

   //FILE TYPE
  info->file_type = getFileType(file_name);

  //FILE SIZE
  sprintf(bufs, "%lu", buf.st_size);
  info->file_size = bufs;

  //FILE ACCESS PERMISSIONS
  sprintf(buffer, "%s", (buf.st_mode & S_IRUSR) ? "r" : "-");
  strcat(buffer, (buf.st_mode & S_IWUSR) ? "w" : "-");
  info->file_access=buffer;

  //LAST ACCESS DATE
  struct tm *access;
  access = localtime(&buf.st_atime);
  sprintf(aux, "%d-%d-%dT%d:%d:%d", access->tm_year + 1900, access->tm_mon + 1, access->tm_mday, access->tm_hour +1 , access->tm_min +1, access->tm_sec);
  info->file_access_date=aux;

  //LAST MODIFICATION DATE
  struct tm *modification;
  modification = localtime(&buf.st_mtime);
  sprintf(str, "%d-%d-%dT%d:%d:%d", modification->tm_year + 1900, modification->tm_mon + 1, modification->tm_mday, modification->tm_hour +1 , modification->tm_min +1, modification->tm_sec);
  info->file_modification_date = str;

  //MD5
  info->md5 = getMD5(file_name);

  //SHA1
  info->sha1 = getSha1Sum(file_name);

  //SHA256
  info->sha256 = getSha256Sum(file_name);

  return 0;
}

char* getStringWithInfo(file_info *info){
  char* str = (char *)malloc(MAX_STRING_LENGTH*sizeof(char));
  if (str == NULL)
    return NULL;

  strcpy(str, info->file_name);
  strcat(str, ", ");
  strcat(str, info->file_type);

  strcat(str, ", ");
  strcat(str, info->file_size);

  strcat(str, ", ");
  strcat(str, info->file_access);

  strcat(str, ", ");
  strcat(str, info->file_access_date);

  strcat(str, ", ");
  strcat(str, info->file_modification_date);

  if(hash_options.md5){
    strcat(str, ", ");
    strcat(str, info->md5);}

  if(hash_options.sha1){
    strcat(str, ", ");
    strcat(str, info->sha1);}

  if(hash_options.sha256){
    strcat(str, ", ");
    strcat(str, info->sha256);}

  return str;
}

void parse_file(char *file){
  struct file_info* info= malloc(sizeof(file_info));
  char* str = (char *)malloc(MAX_STRING_LENGTH*sizeof(char));
  getFileInfo(file, info);
  str = getStringWithInfo(info);
  fprintf(output_file, "%s\n", str);
}
