#include "parser.h"
#include "builtin.h"
#include <string.h>
#include <stdio.h>
#include <glob.h>

int to_tokens(char* input, char TOKENS_2D) {
    char *token = strtok(input, " ");
    int i = 0;
    while(token != NULL) {
        strcpy(tokens[i],token);
        token = strtok(NULL, " ");
        i++;
    }
    return i;
}

bool is_builtin(int tokn, char TOKENS_2D, const char* builtins[BUILTIN_NUM]) {
    int i;
    for (i = 0; i < BUILTIN_NUM; i++) {
        if (strcmp(tokens[0],builtins[i])==0) {
            return true;
        }
    }
    return false;
}


void expand_wildcard(int tokn, char TOKENS_2D) {
    if (tokn < 2) return;
    glob_t globbuf;
    globbuf.gl_offs = 1;
    
    glob(tokens[1], GLOB_DOOFFS | GLOB_NOCHECK, NULL, &globbuf);
    int i;
    for (i=2; i < tokn; i++) {
        glob(tokens[1], GLOB_DOOFFS | GLOB_NOCHECK | GLOB_APPEND, NULL, &globbuf);
    }
    globbuf.gl_pathv[0] = tokens[0];
    printf("cnt: %d\ncmd:%s\n", (int)globbuf.gl_pathc, globbuf.gl_pathv[0]);
}

void join_tokens(int tokn, char TOKENS_2D, char* command) {
    int i;
    // initiate with an empty string
    command[0] = '\0';
    for (i=0 ;i < tokn ;i++) {
        strcat(command, strcat(tokens[i]," "));
    }
    // delete tailing space
    command[strlen(command)-1] = '\0';
}
