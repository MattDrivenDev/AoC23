#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* https://adventofcode.com/2023/day/1 */
int main () {
    
    const char read[] = "r";
    const char filename[] = "input.txt";
    
    FILE *file = fopen(filename, read);
    size_t length;
    int i, number, result;
    char line[256], first, last, full[2];

    while (fgets(line, sizeof(line), file)) {
        length = strlen(line);
        printf("[length=%d] %s", length, line);

        i = 0;
        while (i < length) {
            if (isdigit(line[i]) > 0) {
                first = line[i];
                printf("    first=%c;\n", first);
                break;
            }
            i++;
        }

        i = length - 1;
        while (i >= 0) {
            if (isdigit(line[i]) > 0) {
                last = line[i];
                printf("    last=%c;\n", last);
                break;
            }
            i--;
        }

        sprintf(full, "%c%c", first, last);
        printf("    full=%s;\n", full);
        number = atoi(full);
        result = result + number;
    }

    printf("FINAL RESULT = %d", result);

    fclose(file);

    return 0;
}