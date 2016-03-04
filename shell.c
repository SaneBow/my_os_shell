#include "shell.h"
#include "env.h"
#include "parser.h"
#include "builtin.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>


void sig_handler(int signum) {
    printf("\n");
    shell_prompt(PS1);
}


void handle_signal(bool sig_ignored) {
    if (sig_ignored) {
        signal(SIGINT,sig_handler);
        signal(SIGQUIT,sig_handler);
        signal(SIGTERM,sig_handler);
        signal(SIGTSTP,sig_handler);
    } else {
        signal(SIGINT,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);
        signal(SIGTERM,SIG_DFL);
        signal(SIGTSTP,SIG_DFL);
    }
}


void shell_prompt(char* ps) {
    printf("[%s:%s] ", ps, get_cwd());
    fflush(stdout);
}


void get_input(char* buf_in) {
    if (fgets(buf_in, INPUT_BUF_SIZE, stdin)==NULL) {
        exit(0);
    }
    buf_in[strlen(buf_in)-1] = '\0';
}

bool parse_input(char* input, char* command, glob_t* globbuf) {
    char TOKENS_2D;
    int tokn = to_tokens(input, tokens);
    bool is_bltin = is_builtin(tokn, tokens, BUILTIN_LIST);
    expand_wildcard(tokn, tokens, globbuf);
    join_tokens(tokn, tokens, command);
    return is_bltin;
}


void builtin_exec(char* command) {
    // count # of args by counting spaces
    int argn = 0;
    char* pch = strchr(command, ' ');
    while (pch!=NULL) {
        argn++;
        pch = strchr(pch+1,' ');
    }
    // parse command into func and args
    char args[argn][INPUT_BUF_SIZE];
    char func[INPUT_BUF_SIZE];
    char *token = strtok(command, " ");
    int i = -1;
    while(token != NULL) {
        if (i == -1) 
            strcpy(func, token);
        else
            strcpy(args[i],token);
        token = strtok(NULL, " ");
        i++;
    }
    builtin(func, args, argn);
}


void os_exec(glob_t * globbuf) {
    printf("os: %s\n", globbuf->gl_pathv[0]);
}

