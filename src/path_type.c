#include "path_type.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

path_type get_path_type(char *path)
{
    path_type output;
    struct stat path_info;

    if (stat(path, &path_info) == 0)
    {
        if (S_ISDIR(path_info.st_mode))
            output = DIRECTORY;
        else if (S_ISREG(path_info.st_mode))
            output = FILE_PATH;
        else
            output = ERROR;
    }
    else
        output = ERROR;

    return output;
}
