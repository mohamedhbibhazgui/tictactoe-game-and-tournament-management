#ifndef TYPE_H
#define TYPE_H
typedef struct Player {
    int id;
    char name[50];
    int wins;
    int losses;
    int draws;
} Player;
typedef struct Match {
    int id;
    int player1_id;
    int player2_id;
    int result;
} Match;
#endif