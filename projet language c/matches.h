#ifndef MATCHES_H
#define MATCHES_H

#include "type.h"

Match *find_match_by_id(Match *matches, int mcount, int id);
int add_match(Match *matches, int *mcount, int p1, int p2);
int set_match_result(Match *matches, int mcount, int id, int result);
void print_matches(Match *matches, int mcount);

#endif
