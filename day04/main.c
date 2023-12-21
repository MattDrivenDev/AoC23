#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern void trimstr(char *str);

// https://adventofcode.com/2023/day/4
int main() {

    // It's C o'clock mofo... let's... gooooo!
    // Some of this is starting to look quite a lot more familiary now.
    char filename[] = "input.txt";
    FILE *file = fopen(filename, "r");

    const char delim[] = " ";
    const int offset = strlen("Card "); 

    char *colon, *pipe, *winningstr, *ourstr, *token;
    char line[256], cardnostr[4];
    int *winningno, *ourno;
    int colonidx = 0;
    int cardno = -1;
    int pipeidx = 0;
    int winningcount = 0;
    int ourcount = 0;    
    int result = 0;

    // I think that we can score this one with a single iteration of the file.
    // It looks a little easier on the surface than day03 certainly.
    while (fgets(line, sizeof(line), file)) {

        // Much like in day02 there is an identifier for each line. It isn't
        // relied upon to get the answer in this exercise, but it will make
        // debugging a lot easier if I can output the card number to check.
        // So we get the position of the colon - the card number will be to
        // the left, and the numbers to the right.
        colon = strchr(line, ':');
        colonidx = (int)(colon - line);
        strncpy(cardnostr, line+offset, colonidx-offset);
        cardno = atoi(cardnostr);

        // Now we need to get the list of winning numbers on the right of 
        // the colon, but the left of the pipe. The method is similar but
        // we'll tokenize on the ' ' character to get the numbers. We can
        // even leave them as token strings and compare them as strings.
        pipe = strchr(line, '|');
        pipeidx = (int)(pipe - line);
        winningstr = (char *)malloc(pipeidx-colonidx);
        strncpy(winningstr, line+colonidx+1, pipeidx-colonidx-1);
        winningstr[pipeidx-colonidx-1] = '\0'; // null terminate
        trimstr(winningstr);

        // Heck, we can just use the same method now to get our numbers,
        // which are right of the pipe until the end of the line.
        ourstr = (char *)malloc(strlen(line)-pipeidx);
        strncpy(ourstr, line+pipeidx+1, strlen(line)-pipeidx-1);
        ourstr[strlen(line)-pipeidx-1] = '\0'; // null terminate
        trimstr(ourstr);
        
        // I want to dynamically size the array of numbers, but since 
        // all of the cards are equal in size, I can do so just once.
        // That is going to involve tokenizing the winningstr and ourstr
        // once to size, and then again to populate the arrays. But, once
        // sized, we only just populate arrays.
        if (winningcount == 0) {
            // Clone the winningstr so that we can tokenize it.
            char *winningstrclone = (char *)malloc(strlen(winningstr));
            strcpy(winningstrclone, winningstr);
            token = strtok(winningstrclone, delim);
            while (token != NULL) {
                winningcount++;
                token = strtok(NULL, delim);
            }
            winningno = (int *)malloc(winningcount * sizeof(int));
        }

        if (ourcount == 0) {
            // Clone the ourstr so that we can tokenize it.
            char *ourstrclone = (char *)malloc(strlen(ourstr));
            strcpy(ourstrclone, ourstr);
            token = strtok(ourstrclone, delim);
            while (token != NULL) {
                ourcount++;
                token = strtok(NULL, delim);
            }
            ourno = (int *)malloc(ourcount * sizeof(int));
        }

        // TODO: There is a BUG here. The first card is not fine.
        // Aha! strtok() is destructive. It is modifying the original
        // string. So we need to make a copy of the string before we
        // tokenize it. But, that happens in the above code. I'm just
        // leaving this comment here so that I remember.

        printf("CARD %d\n", cardno);
        printf("   Winning numbers:\n");
        // Now we can populate the arrays with the numbers.
        token = strtok(winningstr, delim);
        for (int i = 0; i < winningcount; i++) {
            winningno[i] = atoi(token);
            token = strtok(NULL, delim);
            printf("      %d\n", winningno[i]);
        }
        printf("   Our numbers:\n");
        token = strtok(ourstr, delim);
        for (int i = 0; i < ourcount; i++) {
            ourno[i] = atoi(token);
            token = strtok(NULL, delim);
            printf("      %d\n", ourno[i]);
        }

        // Now to compare our numbers with the winning numbers. Remember,
        // a score of 1 is awarded for a matching number - and then for
        // each subsequent matching number the score is doubled. 
        // e.g.:
        // 1 match = 1 point
        // 2 matches = 2 points
        // 3 matches = 4 points
        // 4 matches = 8 points
        int score = 0;
        for (int i = 0; i < ourcount; i++) {
            for (int j = 0; j < winningcount; j++) {
                if (ourno[i] == winningno[j]) {
                    score = score == 0 ? 1 : score * 2;
                    printf("   MATCH: %d\n", ourno[i]);
                }
            }
        }
        printf("   SCORE: %d\n", score);
        result += score;
    }

    fclose(file);

    printf("RESULT: %d\n", result);

    return 0;
}