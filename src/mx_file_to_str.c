#include "../inc/header.h"

char *mx_file_to_str(const char *filename) {
    int file = open(filename, O_RDONLY);
    
    if (file < 0) {
        return NULL;
    }
    
    char *str = mx_strnew(1), *c = mx_strnew(1);
    
    while (read(file, c, 1)) {
        str = mx_strjoin(str, c);
    }
    
    close(file);
    return str;
}
