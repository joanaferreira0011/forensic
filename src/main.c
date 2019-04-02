#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include "command.h"
#include "file_parser.h"
#include "generate_log.h"

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

void print_command_options(command_details details) {
  printf(command_print_format,
    bool_to_string(details.recursive),
    bool_to_string(details.hash_md5),
    bool_to_string(details.hash_sha1),
    bool_to_string(details.hash_sha256),
    bool_to_string(details.generate_log),
    details.path_to_log_file,
    bool_to_string(details.output_to_file),
    details.path_to_output_file,
    details.path_to_target);
}

int main(int argc, char *argv[]) {
  
  command_details details;
  if (process_command(argc, argv, &details)) {
    fprintf(stderr, "Could not process command.\n");
    exit(EXIT_FAILURE);
  }

  if (details.generate_log) {
    openLogfile();
  }

  print_command_options(details);
  parse_file(&details);
  exit(EXIT_SUCCESS);
}
