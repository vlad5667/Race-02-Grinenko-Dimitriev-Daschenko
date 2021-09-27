#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct node {
    struct Point pt;
    int dist;
};

struct queue {
    struct node *nodes;
    int head;
    int tail;
};

void mx_printerr(const char *str);
void mx_printchar(char c);
void mx_printint(int n);
void mx_printstr(const char *str);
bool mx_isspace(char c);
bool mx_isdigit(char c);
char *mx_strcat(char *s1, const char *s2);
char *mx_strdup(const char *str);
char *mx_strjoin(char const *s1, char const *s2);
int mx_strlen(const char *s);
char *mx_strnew(const int size);
char *mx_strcpy(char *dst, const char *src);
int mx_strcmp(const char *s1, const char *s2);
char *mx_file_to_str(const char *filename);
char *mx_strstr(const char *s1, const char *s2);
int mx_strncmp(const char *s1, const char *s2, int n);
char *mx_strchr(const char *s, int c);
int mx_atoi(const char *str);
char *mx_strtrim(const char *str);
char *mx_strncpy(char *dst, const char *src, int len);
