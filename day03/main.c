#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Don't forget to compile ..\utils\util.c */
extern void trimstr(char *str);

// https://adventofcode.com/2023/day/3
int main() {
    
    const char filename[] = "input.txt";
    FILE *file = fopen(filename, "r");    

    // Okay, so the file needs two passes to create the dynamic 2D array.
    // First, we need to count the number of rows and columns and allocate
    // the memory for the array. 
    int rowcount = 0, colcount = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (rowcount == 0) colcount++;
        if (c == '\n') rowcount++;
    }
    printf("rowcount=%d, colcount=%d\n", rowcount, colcount);
    char **data = (char **)malloc(rowcount*sizeof(char *));
    for (int i = 0; i < rowcount; i++) {
        data[i] = (char *)malloc(colcount*sizeof(char));
    }

    // Seconndly, we need to read the file again and populate the array.
    rewind(file);
    for (int row = 0; row < rowcount; row++) {
        for (int col = 0; col < colcount; col++) {
            c = fgetc(file);
            if (c != EOF && c != '\n') {
                data[row][col] = c;
            } else {
                data[row][col] = '\0';
            }
        }
    }
    fclose(file);

    // Alrighty then, now we have the data in a 2D array we can start doing
    // the actual work.
    for (int row = 0; row < rowcount; row++) {
        for (int col = 0; col < colcount; col++) {            
            // Only check row above if we're not on the first row.
            if (row > 0) {

            }

            // Only check row below if we're not on the last row.
            if (row < rowcount - 1) {

            }

            // Only check column to the left if we're not on the first column.
            if (col > 0) {

            }

            // Only check column to the right if we're not on the last column.
            if (col < colcount - 1) {

            }
        }
    }

    return 0;
}