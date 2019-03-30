#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <stdbool.h>

struct command_details{
  bool recursive;
  bool hash_md5, hash_sha1, hash_sha256;
  bool generate_log;
  char *path_to_log_file;
  bool output_to_file;
  char *path_to_output_file;
  char *path_to_target;
};

typedef struct command_details command_details;

int process_command(int argc, char *argv[], command_details *details);

#endif/*__COMMAND_H__*/