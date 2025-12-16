#ifndef GAME_H
#define GAME_H
#include "type.h"
char **alloc_move_history(int max_moves);
void free_move_history(char **hist, int max_moves);
void init_board(char **board, int N);
void print_board(char **board, int N);
int make_move(char **board, int N, int row, int col, char symbol);
int check_victory(char **board, int N, int K, char symbol);
int is_board_full(char **board, int N);
int play_match_interactive(Match *m, Player *p1, Player *p2, int N, int K);
#endif