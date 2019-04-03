#ifndef __FILE_PARSER_H__
#define __FILE_PARSER_H__

#include<stdio.h>
#include <string.h>
#include "command.h"

#define MAX_STRING_LENGTH 120

int set_external_output_file(char *path_to_output_file);

void set_output_to_stdout();

typedef struct {
  bool md5;
  bool sha1;
  bool sha256;
} hash_options_t;

void set_hash_options(hash_options_t new_options);

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

void parse_file(char *file);

#endif/*__FILE_PARSER_H__*/
