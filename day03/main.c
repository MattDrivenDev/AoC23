#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Don't forget to compile ..\utils\util.c */
extern void trimstr(char *str);
int issymbol(char c);

// https://adventofcode.com/2023/day/3
int main() {
    
    const char filename[] = "input.txt";
    FILE *file = fopen(filename, "r");    
    int result = 0;

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
    // the actual work here.
    // The input doesn't have numbers that are larger than 3 digits, so we only
    // need a char array of size 3 to store the number. Ideally, this might be 
    // dynamically allocated, but I'm not going to bother with that in this 
    // exercise... It is noise that the exercise doesn't need.
    char number[] = "\0\0\0";
    int adjsym = 0;
    for (int row = 0; row < rowcount; row++) {
        for (int col = 0; col < colcount; col++) {

            // We only want to continue processing if the current position
            // is a numeric digit. This feels like a push/pop stack operation
            // actually, but I don't think that there are types for that out
            // of the box in C? I'm not sure. I'm not a C programmer.
            if (!isdigit(data[row][col])) {

                // If we're not on a digit we might need to pop the stack
                // if there is a number aggregated in the array. If there
                // is a digit in the 1st position we can pop it if it was
                // not adjacent to a symbol.
                if (number[0] != '\0' && adjsym == 1) {
                    int n = atoi(number);
                    result = result + n;
                    printf("Found number: %d - result so far: %d\n", n, result);
                }

                // Reset everything and continue.
                number[0] = '\0';
                number[1] = '\0';
                number[2] = '\0';
                adjsym = 0;
                continue;

            } else {
                // If it is a digit, begin aggregating the number.
                for (int i = 0; i < 3; i++) {
                    if (number[i] == '\0') {
                        number[i] = data[row][col];
                        break;
                    }
                }
            }

            // Only check row above if we're not on the first row. Numbers
            // only run horizontally so other digits and . are ignored.
            if (row > 0) {
                if (issymbol(data[row-1][col]) > 0) adjsym = 1;
                // Only check the above-left diagonal if we're not on the
                // first column.
                if (col > 0) {
                    if (issymbol(data[row-1][col-1]) > 0) adjsym = 1;
                }
                // Only check the above-right diagonal if we're not on the
                // last column.
                if (col < colcount - 1) {
                    if (issymbol(data[row-1][col+1]) > 0) adjsym = 1;
                }
            }

            // Only check row below if we're not on the last row.
            if (row < rowcount - 1) {
                if (issymbol(data[row+1][col]) > 0) adjsym = 1;
                // Only check the below-left diagonal if we're not on the
                // first column.
                if (col > 0) {
                    if (issymbol(data[row+1][col-1]) > 0) adjsym = 1;
                }
                // Only check the below-right diagonal if we're not on the
                // last column.
                if (col < colcount - 1) {
                    if (issymbol(data[row+1][col+1]) > 0) adjsym = 1;
                }
            }

            // Only check column to the left if we're not on the first column.
            if (col > 0) {
                if (issymbol(data[row][col-1]) > 0) adjsym = 1;
            }

            // Only check column to the right if we're not on the last column.
            if (col < colcount - 1) {
                if (issymbol(data[row][col+1]) > 0) adjsym = 1;
            }
        }
    }

    printf("Result: %d\n", result);

    return 0;
}

int issymbol(char c) {
    // Returns 1 if the character is a symbol. Otherwise, returns 0.
    // In this game, a symbol is a character that is not a digit or a dot.
    if (isdigit(c) == 0 && c != '.' && c != '\0' && c != '\n') return 1;
    return 0;
}