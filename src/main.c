#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include "command.h"
#include "file_parser.h"
#include "path_type.h"
#include "generate_log.h"
#include "dir_parser.h"

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
    fprintf(stderr, "main: could not process command.\n");
    exit(EXIT_FAILURE);
  }

  if (details.generate_log) {
    if(openLogfile(details.path_to_log_file))
      exit(EXIT_FAILURE);
  }

  if (details.output_to_file) {
    if (set_external_output_file(details.path_to_output_file))
      exit(EXIT_FAILURE);
  }
  else
    set_output_to_stdout();

  hash_options_t hash_options = {
    .md5 = details.hash_md5,
    .sha1 = details.hash_sha1,
    .sha256 = details.hash_sha256
  };
  set_hash_options(hash_options);

  //print_command_options(details);
  //parse_file(details.path_to_target);
  check_dir(details.path_to_target, details.recursive);
  exit(EXIT_SUCCESS);
}
