#include <stdio.h>
#include <string.h>
#include "players.h"
#include "matches.h"
#include "game.h"
#include "fileio.h"
#include "utils.h"
#define MAX_PLAYERS 100
#define MAX_MATCHES 1000
#define N 3
#define K 3
#define FILENAME "players_matches.txt"
int main(void) {
    Player players[MAX_PLAYERS];
    Match matches[MAX_MATCHES];
    int pcount = 0;
    int mcount = 0;
    int choix;
    if (load_tournament(FILENAME, players, &pcount, matches, &mcount) == -1) {
        printf("il n'ya pas un tournoi\n");
    } else {
        printf("tournoi trouvé\n");
    }
    do {
        printf("\nmenu\n");
        printf("1 ajouter joueur\n");
        printf("2 supprimez joueur\n");
        printf("3 afficher joueur\n");
        printf("4 afficher match\n");
        printf("5 jouez\n");
        printf("6 sauvegardez\n");
        printf("0 quittez\n");
        if (!safe_read_int("Choice: ", &choix, 0, 6)) {
            continue;
        }
        switch (choix) {
        case 1: {
            char name[50];
            printf("nom du joueur:");
            fgets(name, sizeof(name), stdin);
            strip_newline(name);
            if (add_player(players, &pcount, name)) {
                printf("joueur ajouté\n");
            } else {
                printf("joueur non ajouté\n");
            }
            break;
        }
        case 2: {
            int id;
            if (safe_read_int("id du joueur pour supprimer", &id, 1, pcount)) {
                if (remove_player(players, &pcount, matches, mcount, id)) {
                    printf("joueur supprimé\n");
                } else {
                    printf("tu ne peut pas supprimer cette joueur(car il est dans un match) \n");
                }
            }
            break;
        }
        case 3:
            print_players(players, pcount);
            break;
        case 4:
            print_matches(matches, mcount);
            break;
        case 5: {
            int p1_id, p2_id;
            Player *p1, *p2;
            if (pcount < 2) {
                printf("il n'ya pas du joeur suffisants\n");
                break;
            }
            safe_read_int("joueur 1 ID: ", &p1_id, 1, pcount);
            safe_read_int("joueur 2 ID: ", &p2_id, 1, pcount);
            p1 = find_player_by_id(players, pcount, p1_id);
            p2 = find_player_by_id(players, pcount, p2_id);
            if (!p1 || !p2 || p1_id == p2_id) {
                printf("id invalide\n");
                break;
            }
            if (!add_match(matches, &mcount, p1_id, p2_id)) {
                printf("ne peut pas ajoutez le match\n");
                break;
            }
            Match *m = &matches[mcount - 1];
            play_match_interactive(m, p1, p2, N, K);
            printf("Match fini\n");
            break;
        }
        case 6:
            if (save_tournament(FILENAME, players, pcount, matches, mcount) == 0) {
                printf("tournoi sauvegardé\n");
            }
            break;
        case 0:
            printf("programme fini\n");
            break;
        default:
            break;
        }
    } while (choix != 0);
    return 0;
}
