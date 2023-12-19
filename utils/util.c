#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void trimstr(char *str) {
    char *p = str;
    int l = strlen(p);
    while (isspace(p[l - 1])) p[l--] = 0;
    while (*p && isspace(*p)) p++, l--;
    memmove(str, p, l + 1);
}

void trimcntrl(char *str) {
    char *p = str;
    int l = strlen(p);
    while (iscntrl(p[l - 1])) p[l--] = 0;
    while (*p && iscntrl(*p)) p++, l--;
    memmove(str, p, l + 1);
}