#include <stdio.h>
#include <string.h>
#include "fileio.h"
#define MAX_PLAYERS 100
#define MAX_MATCHES 1000
int load_tournament(const char *filename, Player *players, int *pcount, Match *matches, int *mcount) {
    FILE *f;
    char line[4096];
    char *token;
    *pcount = 0;
    *mcount = 0;
    f = fopen(filename, "r");
    if (f == NULL) {
        return -1;
    }
    if (fgets(line, sizeof(line), f) != NULL) {
        if (strncmp(line, "PLAYERS", 7) == 0) {
            token = strtok(line + 7, " \n");
            while (token != NULL && *pcount < MAX_PLAYERS) {
                if (sscanf(token, "%d;%49[^;];%d;%d;%d",
                           &players[*pcount].id,
                           players[*pcount].name,
                           &players[*pcount].wins,
                           &players[*pcount].losses,
                           &players[*pcount].draws) == 5) {
                    (*pcount)++;
                }
                token = strtok(NULL, " \n");
            }
        }
    }
    if (fgets(line, sizeof(line), f) != NULL) {
        if (strncmp(line, "MATCHES", 7) == 0) {
            token = strtok(line + 7, " \n");
            while (token != NULL && *mcount < MAX_MATCHES) {
                if (sscanf(token, "%d;%d;%d;%d",
                           &matches[*mcount].id,
                           &matches[*mcount].player1_id,
                           &matches[*mcount].player2_id,
                           &matches[*mcount].result) == 4) {
                    (*mcount)++;
                }
                token = strtok(NULL, " \n");
            }
        }
    }
    fclose(f);
    return 0;
}
int save_tournament(const char *filename, Player *players, int pcount, Match *matches, int mcount) {
    FILE *f;
    int i;

    f = fopen(filename, "w");
    if (f == NULL) {
        return -1;
    }
    fprintf(f, "PLAYERS");
    for (i = 0; i < pcount; i++) {
        fprintf(f, " %d;%s;%d;%d;%d",
                players[i].id,
                players[i].name,
                players[i].wins,
                players[i].losses,
                players[i].draws);
    }
    fprintf(f, "\n");
    fprintf(f, "MATCHES");
    for (i = 0; i < mcount; i++) {
        fprintf(f, " %d;%d;%d;%d",
                matches[i].id,
                matches[i].player1_id,
                matches[i].player2_id,
                matches[i].result);
    }
    fprintf(f, "\n");
    fclose(f);
    return 0;
}
