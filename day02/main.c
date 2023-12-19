#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED     12
#define GREEN   13
#define BLUE    14

void trim(char *str);
int getvalue(char *str);

/* https://adventofcode.com/2023/day/2 */
int main() {
    
    const char read[] = "r";
    const char filename[] = "input.txt";
    
    FILE *file = fopen(filename, read);
    size_t length;
    char line[256], *colon;
    int i, gameid, colonidx, gameidsize, validgame;
    const char delim[] = ";,";
    int result = 0;

    while (fgets(line, sizeof(line), file)) {
        length = strlen(line);

        // Assume game is valid until rules are broken
        validgame = 1;

        // First, parse the gameid
        // It starts at position 5 of the line, and ends at ":" -1
        colon = strchr(line, ':');
        colonidx = (int)(colon - line);
        gameidsize = colonidx - 5;
        char gameidstr[3];
        strncpy(gameidstr, line + 5, gameidsize);        
        trim(gameidstr);
        printf("[gameid=%s]\n", gameidstr);
        // ********************************************************************

        // Secondly, parse the hands of games
        // The hands start after the ":", which we already have in the colonidx
        // and they are separated by a ";"
        int handsidx = colonidx + 2;
        int handslen = length - handsidx + 1;
        char *rawhands;
        rawhands = (char *)malloc(handslen);
        strncpy(rawhands, line + handsidx, handslen);
        char *token = strtok(rawhands, delim);
        while (token != NULL) {
            trim(token);

            // Thirdly, apply our game rules - invalidating the game where
            // appropriate value exceeds the number of cubes of that color.
            int value = getvalue(token);
            if (strstr(token, "red") != NULL && value > RED) {
                printf("    red %d exceeds %d\n", value, RED);
                validgame = 0;
            }
            if (strstr(token, "blue") != NULL && value > BLUE) {
                printf("    blue %d exceeds %d\n", value, BLUE);
                validgame = 0;
            }
            if (strstr(token, "green") != NULL && value > GREEN) {
                printf("    green %d exceeds %d\n", value, GREEN);
                validgame = 0;
            }            
            
            // Take next token... strtok has some internal memory!?
            token = strtok(NULL, delim);
        }
        
        // Finally, evaluate this game and aggregate game id if valid.
        gameid = atoi(gameidstr);
        if (validgame == 1) {
            printf("    GAME %d IS POSSIBLE\n", gameid);
            result = result + gameid;
        } else {
            printf("    GAME %d IS IMPOSSIBLE\n", gameid);
        }

        free(rawhands);
    }

    fclose(file);

    printf("RESULT=%d", result);

    return 0;
}

int getvalue(char *str) {
    char *p = str;
    int l = strlen(p);
    int i;
    while (i < l && isdigit(p[i]) > 0) i++;
    char *rawn;
    rawn = (char *)malloc(i + 1);
    strncpy(rawn, str, i + 1);
    int n = atoi(rawn);
    free(rawn);
    return n;
}

void trim(char *str) {
    char *p = str;
    int l = strlen(p);
    while (isspace(p[l - 1])) p[l--] = 0;
    while (*p && isspace(*p)) p++, l--;
    memmove(str, p, l + 1);
}