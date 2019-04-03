#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include "command.h"
#include "file_parser.h"
#include "path_type.h"
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
//
// int check_file(command_details details){
//   //print_command_options(details);
//   parse_file(&details);
//   return 0;
// }

int check_dir(char* dir){

  struct dirent *de;
   DIR *dr = opendir(dir);
    path_type type;
    char* new_dir=(char *)malloc(60*sizeof(char));;
    type= get_path_type(dir);

    if(type==FILE_PATH){
      //command_details* det = (command_details*) malloc(sizeof(command_details));
      // memcpy(det, details, sizeof(command_details));
      // det->path_to_target= dir;
      parse_file(dir);
      // free(det);
      free(new_dir);
      return 0;
    }

    else if (dr == NULL)
    {
       //free(details);
        printf("Could not open current directory\n" );
        free(new_dir);
        return 0;
    }

   while ((de = readdir(dr)) != NULL){
     if(strcmp(de->d_name, "..") && strcmp(de->d_name, ".")){
       strcpy(new_dir, dir);
       strcat(new_dir, "/");
       strcat(new_dir, de->d_name);
       check_dir(new_dir);}
     }


     free(new_dir);
     closedir(dr);
   return 0;
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
  check_dir(details.path_to_target);
  exit(EXIT_SUCCESS);
}
