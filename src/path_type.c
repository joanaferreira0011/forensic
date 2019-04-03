#include "path_type.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

path_type get_path_type(char *path) {
    path_type output;
    struct stat path_info;

    if (stat(path, &path_info) == 0) {
        if (path_info.st_mode & S_IFDIR)
            output = DIRECTORY;
        else if (path_info.st_mode & S_IFREG)
            output = FILE_PATH;
    }
    else
        output = ERROR;
    return output;
}
