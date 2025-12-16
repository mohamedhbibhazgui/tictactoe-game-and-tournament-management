#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "utils.h"
void init_board(char **board, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            board[i][j] = '.';
        }
    }
}
void print_board(char **board, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}
char **alloc_move_history(int max_moves){
    char **h = malloc(max_moves * sizeof(char *));
    for(int i=0;i<max_moves;i++){
        h[i] = malloc(16);
        h[i][0] = '\0';
    }
    return h;
}
void free_move_history(char **hist, int max_moves){
    for(int i=0;i<max_moves;i++) free(hist[i]);
    free(hist);
}
int make_move(char **board, int N, int row, int col, char symbol) {
    row--;
    col--;
    if (row < 0 || row >= N || col < 0 || col >= N) {
        return 0;
    }
    if (board[row][col] != '.') {
        return 0;
    }
    board[row][col] = symbol;
    return 1;
}
int check_victory(char **board, int N, int K, char symbol) {
    int count;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] != symbol) continue;
            count = 0;
            for (int x = j; x < N && board[i][x] == symbol; x++) count++;
            if (count >= K) return 1;
            count = 0;
            for (int x = i; x < N && board[x][j] == symbol; x++) count++;
            if (count >= K) return 1;
            count = 0;
            for (int x = 0; i+x < N && j+x < N && board[i+x][j+x] == symbol; x++) count++;
            if (count >= K) return 1;
            count = 0;
            for (int x = 0; i+x < N && j-x >= 0 && board[i+x][j-x] == symbol; x++) count++;
            if (count >= K) return 1;
        }
    }
    return 0;
}

int is_board_full(char **board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == '.') {
                return 0;
            }
        }
    }
    return 1;
}
int play_match_interactive(Match *m, Player *p1, Player *p2, int N, int K) {
    char **board = malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        board[i] = malloc(N * sizeof(char));
    }
    init_board(board, N);
    print_board(board, N);
    int row, col;
    int turn = 0;
    char symbol;
    Player *current;
    while (1) {
        if (turn == 0) {
            symbol = 'X';
            current = p1;
        } else {
            symbol = 'O';
            current = p2;
        }
        printf("%s (%c), enter row col: ", current->name, symbol);
        if (scanf("%d %d", &row, &col) != 2) {
            clear_stdin_buffer();
            continue;
        }
        if (!make_move(board, N, row, col, symbol)) {
            printf("Invalid move.\n");
            continue;
        }
        print_board(board, N);
        if (check_victory(board, N, K, symbol)) {
            if (turn == 0) {
                m->result = 1;
                p1->wins++;
                p2->losses++;
            } else {
                m->result = 2;
                p2->wins++;
                p1->losses++;
            }
            break;
        }
        if (is_board_full(board, N)) {
            m->result = 3;
            p1->draws++;
            p2->draws++;
            break;
        }
        turn = 1 - turn;
    }
    for (int i = 0; i < N; i++) free(board[i]);
    free(board);
    return m->result;
}
