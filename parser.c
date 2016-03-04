#include "parser.h"
#include "builtin.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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


void expand_wildcard(int tokn, char TOKENS_2D, glob_t* globbuf) {
    globbuf->gl_offs = 1;

    if (tokn < 2) {
        glob("", GLOB_DOOFFS | GLOB_NOCHECK, NULL, globbuf);
        globbuf->gl_pathv[1] = NULL;
        globbuf->gl_pathc -= 1;
    } else {
        glob(tokens[1], GLOB_DOOFFS | GLOB_NOCHECK, NULL, globbuf);
        int i;
        for (i=2; i < tokn; i++) {
            glob(tokens[i], GLOB_DOOFFS | GLOB_NOCHECK | GLOB_APPEND, NULL, globbuf);
        }
    }
    // make a copy of tokens[0] to prevent its change
    char *fname = malloc( (strlen(tokens[0])+1) * sizeof(char) );
    strcpy(fname,tokens[0]);
    globbuf->gl_pathv[0] = fname;
}

