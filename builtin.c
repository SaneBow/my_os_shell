#include "builtin.h"
#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* BUILTIN_LIST[BUILTIN_NUM] = {
    "cd",
    "exit"
};

void builtin(char* func, char** args, int argn) {
    if (strcmp(func, "cd") == 0) {
        if (argn != 1) {
            printf("cd: wrong number of arguments\n");
            return;
        }
        change_dir(args[0]);
    }

    if (strcmp(func, "exit") == 0) {
        if (argn != 0) {
            printf("exit: wrong number of arguments\n");
            return;
        }
        exit(0);
    }
}
