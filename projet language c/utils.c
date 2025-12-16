#include "utils.h"
#include <stdio.h>
#include <string.h>
#include "type.h"
int safe_read_int(const char *prompt, int *out, int min, int max){
    char buffer[100];
    int value;
    while(1){
        printf("%s", prompt);
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            return 0;
        }
        if(sscanf(buffer, "%d", &value) != 1){
            printf("Invalid input. Please enter an integer.\n");
            continue;
        }
        if(value < min || value > max){
            printf("Input out of range (%d to %d). Please try again.\n", min, max);
            continue;
        }
        *out = value;
        return 1;
    }
}
void clear_stdin_buffer(void){
    int c;
    while((c = getchar()) != '\n' && c != EOF); /*fhmtsh belbehi*/
}
void strip_newline(char *s){
    size_t longuer = strlen(s);
    if(longuer > 0 && s[longuer - 1] == '\n'){
        s[longuer - 1] = '\0';
    }
}