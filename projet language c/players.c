#include <stdio.h>
#include <string.h>
#include "players.h"
#include "type.h"
#define MAX_PLAYERS 100
Player *find_player_by_id(Player *players, int pcount, int id) {
    for (int i = 0; i < pcount; i++) {
        if (players[i].id == id) {
            return &players[i];
        }
    }
    return NULL;
}
int add_player(Player *players, int *pcount, const char *name) {
    if (*pcount >= MAX_PLAYERS) {
        return 0;
    }
    int idx = *pcount;
    strncpy(players[idx].name, name, sizeof(players[idx].name) - 1);
    players[idx].name[sizeof(players[idx].name) - 1] = '\0';
    players[idx].id = idx + 1;
    players[idx].wins = 0;
    players[idx].losses = 0;
    players[idx].draws = 0;
    (*pcount)++;
    return 1;
}
int remove_player(Player *players, int *pcount, Match *matches, int mcount, int id){
    int i,j;
    for (i=0;i<mcount;i++){
        if ((matches[i].player1_id == id || matches[i].player2_id == id) && matches[i].result != 0){
            return 0;
        }
    }
    for (i=0;i<*pcount;i++){
        if (players[i].id == id){
            for (j=i;j<*pcount-1;j++){
                players[j] = players[j+1];
                players[j].id = j+1;
            }
            *pcount = *pcount - 1;
            return 1;
        }
    }
    return 0;
}
void print_players(Player *players, int pcount){
    int i;
    for (i=0;i<pcount;i++){
        printf("%d %s %d/%d/%d\n", players[i].id, players[i].name, players[i].wins, players[i].losses, players[i].draws);
    }
}