#ifndef __PATH_TYPE_H__
#define __PATH_TYPE_H__

typedef enum {
    ERROR,
    FILE_PATH,
    DIRECTORY
} path_type;

path_type get_path_type(char *path);

#endif/*__PATH_TYPE_H__*/
