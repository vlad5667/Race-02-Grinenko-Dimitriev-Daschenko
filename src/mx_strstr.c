#include "../inc/header.h"

char *mx_strstr(const char *s1, const char *s2){
    if(mx_strlen(s1) < mx_strlen(s2)) {
        return 0;
    }
    while(*s1 != '\0') {
        if(mx_strncmp(s1, s2, mx_strlen(s2)) == 0) {
            return mx_strchr(s1, *s2);
        }
        s1++;
    }
    return 0;
}
