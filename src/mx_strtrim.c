#include "../inc/header.h"

char *mx_strtrim(const char *str) {
    int i = 0;

    while (mx_isspace(str[i])) {
	    i++;
    }

    int j = mx_strlen(str) - 1;

    while (mx_isspace(str[j])) {
	    j--;
    }

    char *tmp = mx_strnew(j - i + 1);
    mx_strncpy(tmp, str + i, j - i + 1);
    return tmp;
}

