#include "command.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void clear_details(command_details *details) {
    details->recursive = false;
    details->hash_md5 = false;
    details->hash_sha1 = false;
    details->hash_sha256 = false;
    details->output_to_file = false;
    details->generate_log = false;
    details->path_to_log_file = NULL;
    details->path_to_output_file = NULL;
    details->path_to_target = NULL;
}

static int process_input_path(char *argument, command_details *details) {
  char *path = NULL;
  if ((path = strdup(argument)) == NULL)
    return -1;
  details->path_to_target = path;
  return 0;
}

static int process_hash_options(char *argument, command_details *details) {

  if (argument == NULL || details == NULL) {
    printf("null");
    return -2;
  }

  int state = 0;
  for (size_t i = 0; i < strlen(argument); i++) {
    switch (argument[i]) {
      case ',':
        switch (state) {
          case 3:
            state = 4;
            break;
          case 8:
            state = 9;
            break;
          default:
            state = -1;
            break;
        }
        break;

      case '1':
        if (state == 7) {
          state = 8;
          details->hash_sha1 = true;
        }
        else
          state = -1;
        break;

      case '2':
        switch (state) {
          case 7:
          case 12:
            state = 13;
            break;
          default:
            state = -1;
            break;
        }
        break;

      case '5':
        switch (state) {
          case 2:
            state = 3;
            details->hash_md5 = true;
            break;
          case 13:
            state = 14;
            break;
          default:
            state = -1;
            break;
        }
        break;

      case '6':
        if (state == 14) {
          state = 15;
          details->hash_sha256 = true;
        }
        else
          state = -1;
        break;

      case 'a':
        switch (state) {
          case 6:
            state = 7;
            break;
          case 11:
            state = 12;
            break;
          default:
            state = -1;
            break;
        }
        break;

      case 'd':
        if (state == 1)
          state = 2;
        else
          state = -1;
        break;

      case 'h':
        switch (state) {
          case 5:
            state = 6;
            break;
          case 10:
            state = 11;
            break;
          default:
            state = -1;
            break;
        }
        break;

      case 'm':
        if (state == 0)
          state = 1;
        else
          state = -1;
        break;

      case 's':
        switch (state) {
          case 0:
          case 4:
            state = 5;
            break;
          case 9:
            state = 10;
            break;
          default:
            state = -1;
            break;
        }
        break;

      default:
        state = -1;
        break;
    }
    if (state == -1) {
      return -1;
    }
  }
  switch (state) {
    case 3:
    case 8:
    case 15:
      return 0;
      break;
  }
  return -1;
}

static int process_output_option(char *argument, command_details *details) {
  char *path = NULL;
  if ((path = strdup(argument)) == NULL)
    return -1;
  details->path_to_output_file = path;
  return 0;
}

static int process_log_option(command_details *details) {
  char *log_file_path;
  if ((log_file_path = getenv("LOGFILENAME")) == NULL)
    return -1;
  details->path_to_log_file = log_file_path;
  return 0;
}

int process_command(int argc, char *argv[], command_details *details) {
  if (details == NULL)
    return -7;

  clear_details(details);
  extern int optind;
  extern char *optarg;
  int opt;

  while ((opt = getopt(argc, argv, "rh:o:v")) != -1) {
    switch (opt) {
      case 'r':
        details->recursive = true;
        break;
      case 'h':
        if(process_hash_options(strdup(optarg), details))
          return -6;
        break;
      case 'o':
        details->output_to_file = true;
        if(process_output_option(optarg, details))
          return -5;
        break;
      case 'v':
        details->generate_log = true;
        if(process_log_option(details))
          return -4;
        break;
      default:
        return -3;
    }
  }

  if (optind >= argc)
    return -2;

  if (process_input_path(argv[optind], details))
    return -1;

  return 0;
}
