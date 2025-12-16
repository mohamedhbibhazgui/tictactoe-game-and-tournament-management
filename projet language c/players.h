#ifndef PLAYERS_H
#define PLAYERS_H

#include "type.h"

Player *find_player_by_id(Player *players, int pcount, int id);
int add_player(Player *players, int *pcount, const char *name);
int remove_player(Player *players, int *pcount, Match *matches, int mcount, int id);
void print_players(Player *players, int pcount);

#endif
