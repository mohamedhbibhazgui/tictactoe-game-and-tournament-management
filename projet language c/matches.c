#include <stdio.h>
#include "matches.h"
#include "utils.h"
#include "type.h"
int Max_Matches = 1000;
Match *find_match_by_id(Match *matches, int mcount, int id) {
    int i;
    for (i = 0; i < mcount; i++) {
        if (matches[i].id == id) {
            return &matches[i];
        }
    }
    return NULL;
}
int add_match(Match *matches, int *mcount, int p1, int p2) {
    if (*mcount >= Max_Matches) {
        return 0;
    }
    matches[*mcount].id = *mcount + 1;
    matches[*mcount].player1_id = p1;
    matches[*mcount].player2_id = p2;
    matches[*mcount].result = 0;
    (*mcount)++;
    return 1;
}
int set_match_result(Match *matches, int mcount, int id, int result) {
    Match *match = find_match_by_id(matches, mcount, id);
    if (match == NULL) {
        return 0;
    }
    match->result = result;
    return 1;
}
void print_matches(Match *matches, int mcount) {
    int i;
    printf("Matches:\n");
    for (i = 0; i < mcount; i++) {
        printf("Match ID: %d, Player 1 ID: %d, Player 2 ID: %d, Result: %d\n",
               matches[i].id, matches[i].player1_id, matches[i].player2_id, matches[i].result);
    }
}
