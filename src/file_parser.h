//#pragma once

#include<stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 50

struct file_info {
  char* file_name;
  char* file_type;
  char* file_size;
  char* file_access;
  char* file_access_date;
  char* file_modification_date;
  char* md5;
  char* sha1;
  char* sha256;
};
typedef struct file_info file_info;

char* getStringWithInfo(char *file_name, file_info *info);
