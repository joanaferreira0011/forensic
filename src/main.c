#include <string.h>
#include<stdio.h>
#include "file_parser.h"

//Na página 2 na "Apresentação de resultados" em vez de ser file_created_date é file_acess_date

int main(int argc, char *argv[ ], char *envp[ ]){
  char* file_name = argv[1];
  getInfoFile(file_name);
  
}
