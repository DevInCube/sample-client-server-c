#include "string_ext.h"
#include <stdlib.h>

// adapted from https://stackoverflow.com/a/37132824/6634744
char *ft_strdup(char *src) {
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}