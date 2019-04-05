#define _XOPEN_SOURCE
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
#include <signal.h>

int main(int argc, char *argv[])
{

  start_clock();
  command_details details;

  if (process_command(argc, argv, &details))
  {
    fprintf(stderr, "main: could not process command.\n");
    exit(EXIT_FAILURE);
  }

  if (details.generate_log)
  {
    if (openLogfile(details.path_to_log_file))
      exit(EXIT_FAILURE);

    write_to_log_COMMAND(argc, argv);
  }

  if (details.output_to_file)
  {
    if (set_external_output_file(details.path_to_output_file))
      exit(EXIT_FAILURE);
  }
  else
    set_output_to_stdout();

  hash_options_t hash_options = {
      .md5 = details.hash_md5,
      .sha1 = details.hash_sha1,
      .sha256 = details.hash_sha256};
  set_hash_options(hash_options);

  //print_command_options(details);
  check_dir(details.path_to_target, details.recursive);

  if (details.generate_log)
  {
    write_to_log("FINISHED");
    close_log_file();
  }

  exit(EXIT_SUCCESS);
}
