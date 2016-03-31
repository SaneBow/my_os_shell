#include "shell.h"
#include "env.h"
#include "parser.h"
#include "builtin.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>


void sig_handler(int signum) {
    printf("\n");
    shell_prompt(PS1);
    HAS_PROMPT = true;
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
    printf("[%s:%s]$ ", ps, get_cwd());
    fflush(stdout);
}


void get_input(char* buf_in) {
    if (fgets(buf_in, INPUT_BUF_SIZE, stdin)==NULL) {
        exit(0);
    }
    buf_in[strlen(buf_in)-1] = '\0';
}


cmd_t parse_input(char* input, glob_t* globbuf) {
    char TOKENS_2D;
    int tokn = to_tokens(input, tokens);
    if (tokn == 0) {
        return CMD_BLANK;
    }
    bool is_bltin = is_builtin(tokn, tokens, BUILTIN_LIST);
    expand_wildcard(tokn, tokens, globbuf);
    if (is_bltin) {
        return CMD_BUILTIN;
    } else {
        return CMD_OS;
    }
}


void builtin_exec(glob_t* globbuf) {
    int argn = globbuf->gl_pathc;
    // parse command into func and args
    char* func = globbuf->gl_pathv[0];
    char** args = &(globbuf->gl_pathv[1]);
    
    builtin(func, args, argn);
}


void os_exec(glob_t * globbuf) {
    setenv("PATH","/bin:/usr/bin:.",1);
    pid_t child_pid;
    if (!(child_pid = fork())) {
        handle_signal(false);
        char* fname = globbuf->gl_pathv[0];
        execvp(fname, globbuf->gl_pathv);
        if (errno == ENOENT) {
            printf("%s: command not found\n", fname);
        } else {
            printf("%s: unknown error\n", fname);
        }
        exit(-1);
    } else {
        wait(NULL);
    }
}

