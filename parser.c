#include "parser.h"
#include "builtin.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <glob.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

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
    glob_t globbuf;
    globbuf.gl_offs = 1;
    
    if (tokn < 2) {
        glob("", GLOB_DOOFFS | GLOB_NOCHECK, NULL, &globbuf);
        globbuf.gl_pathv[1] = NULL;
    } else {
        glob(tokens[1], GLOB_DOOFFS | GLOB_NOCHECK, NULL, &globbuf);
        int i;
        for (i=2; i < tokn; i++) {
            glob(tokens[i], GLOB_DOOFFS | GLOB_NOCHECK | GLOB_APPEND, NULL, &globbuf);
        }
    }
    globbuf.gl_pathv[0] = tokens[0];

    setenv("PATH","/bin:/usr/bin:.",1);
    pid_t child_pid;
    if (!(child_pid = fork())) {
        execvp(globbuf.gl_pathv[0], globbuf.gl_pathv);
        if (errno == ENOENT) {
            printf("%s: command not found\n", tokens[0]);
        } else {
            printf("%s: unkown error\n", tokens[0]);
        }
        exit(-1);
    } else {
        wait(NULL);
    }
    globfree(&globbuf);
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

