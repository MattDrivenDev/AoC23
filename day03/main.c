#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Don't forget to compile ..\utils\util.c */
extern void trimstr(char *str);
extern void trimcntrl(char *str);

// https://adventofcode.com/2023/day/3
int main() {
    
    const char filename[] = "input.txt";
    FILE *file = fopen(filename, "r");
    size_t length;
    char line[256];    

    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        trimstr(line);
        trimcntrl(line);
        length = strlen(line);
        printf("%d=%d;%s", i + 1, length, line);
        i++;
    }

    return 0;
}