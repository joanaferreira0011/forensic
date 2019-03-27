#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>

static struct {
  bool recursive;
  bool hash_md5, hash_sha1, hash_sha256;
  bool generate_log;
  bool output_to_file;
} command_options;

static struct {
  char * path;
  int descriptor;
} output_file, log_file, start_file;

void init_command_options() {
  command_options.recursive = false;
  command_options.hash_md5 = false;
  command_options.hash_sha1 = false;
  command_options.hash_sha256 = false;
  command_options.generate_log = false;
  command_options.output_to_file = false;
}

void init_file_structs() {
  output_file.path = NULL;
  output_file.descriptor = -1;
  log_file.path = NULL;
  log_file.descriptor = -1;
  start_file.path = NULL;
  start_file.descriptor = -1;
}

char *clone_string(char *string) {
  if (string == NULL)
    return NULL;
  size_t buffer_size = strlen(string) + 1;
  char *clone = malloc(buffer_size);
  if (clone == NULL)
    return NULL;
  memcpy(clone, string, buffer_size);
  return clone;
}

int process_hash_options(char *argument) {
  if (argument == NULL) {
    return -2;
  }
  char *temp = argument;
  char* token;
  while (!(token = (char*)strtok(temp, ","))) {
    temp = NULL;
    if (strncmp (token, "md5", 3) == 0) {
      command_options.hash_md5 = true;
    } else if (strncmp(token, "sha1", 4) == 0) {
      command_options.hash_sha1 = true;
    } else if (strncmp(token, "sha256", 6) == 0) {
      command_options.hash_sha256 = true;
    } else return -1;
  }
  return 0;
}

int process_output_option(char *argument) {
  char *path = NULL;
  if ((path = clone_string(argument)) == NULL)
    return -1;
  output_file.path = path;
  return 0;
}

int process_log_option() {
  char *log_file_path;
  if ((log_file_path = getenv("LOGFILENAME")) == NULL)
    return -1;
  log_file.path = log_file_path;
  return 0;
}

int process_input_path(char *argument) {
  char *path = NULL;
  if ((path = clone_string(argument)) == NULL)
    return -1;
  start_file.path = path;
  return 0;
}



int process_command(int argc, char *argv[]) {
  init_command_options();
  init_file_structs();
  extern int optind;
  extern char *optarg;
  int opt;

  while ((opt = getopt(argc, argv, "rh:o:v")) != -1) {
    switch (opt) {
      case 'r':
        command_options.recursive = true;
        break;
      case 'h':
        if(process_hash_options(optarg)) {
          fprintf(stderr, "Error: invalid hash options.\n");
          return -6;
        }
        break;
      case 'o':
        command_options.output_to_file = true;
        if(process_output_option(optarg)) {
          fprintf(stderr, "Error: invalid file ouptut option.\n");
          return -5;
        }
        break;
      case 'v':
        command_options.generate_log = true;
        if(process_log_option()) {
          fprintf(stderr, "Error: invalid log option.\n");
          return -4;
        }
        break;
      default:
        fprintf(stderr, "Error: unexpected argument.\n");
        return -3;
    }
  }

  if (optind >= argc) {
    fprintf(stderr,"Error: no target file provided.\n");
    return -2;
  }

  if (process_input_path(argv[optind])) {
    fprintf(stderr,"Error: could not open file.\n");
    return -1;
  }

  return 0;
}

const char *bool_to_string(bool val) {
  return (val ? "true" : "false");
}

const char * command_print_format =
  "Flags: \n"
  "Recursive = %s\n"
  "Hash:\n"
  "\tMD5 = %s\n"
  "\tSHA1 = %s\n"
  "\tSHA256 = %s\n"
  "Logging = %s\n"
  "Log file path = %s\n"
  "File output = %s\n"
  "Output file path = %s\n"
  "Input file path = %s\n";

void print_command_options() {
  printf(command_print_format,
    bool_to_string(command_options.recursive),
    bool_to_string(command_options.hash_md5),
    bool_to_string(command_options.hash_sha1),
    bool_to_string(command_options.hash_sha256),
    bool_to_string(command_options.generate_log),
    log_file.path,
    bool_to_string(command_options.output_to_file),
    output_file.path,
    start_file.path);
}

int main(int argc, char *argv[]) {
  if (process_command(argc, argv)) {
    fprintf(stderr, "Could not process command.\n");
    exit(EXIT_FAILURE);
  }
  print_command_options();
  exit(EXIT_SUCCESS);
}
