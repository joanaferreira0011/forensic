#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "path_type.h"
#include "dir_parser.h"
#include "file_parser.h"
#include <unistd.h>
#include <sys/types.h>

int check_dir(char* path){
  struct dirent *de;
  DIR *dr = opendir(path);
  path_type type;
  char* new_path=(char *)malloc(60*sizeof(char));
  int pid;
  // type= get_path_type(path);
  //
  //   if(type==FILE_PATH){
  //     parse_file(path);
  //     free(new_path);
  //     return 0;
  //   }

    if (dr == NULL)
    {
        printf("Could not open current pathectory\n" );
        free(new_path);
        return 0;
    }



   while ((de = readdir(dr)) != NULL){
     if(strcmp(de->d_name, "..") && strcmp(de->d_name, ".")){
       strcpy(new_path, path);
       strcat(new_path, "/");
       strcat(new_path, de->d_name);

       type= get_path_type(new_path);
       if(type==DIRECTORY){
         pid=fork();
         if(pid==0)
          {
           check_dir(new_path);
           break;
         }
   }
         else (type==FILE_PATH){
           printf("oi?\n");
           parse_file(path);
           free(new_path);
           continue;
         }

      }
     }

  free(new_path);
  closedir(dr);

  return 0;
}
