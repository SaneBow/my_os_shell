#include "env.h"
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

char* get_cwd(void) {
    static char cwd[PATH_MAX+1];
    if(getcwd(cwd,PATH_MAX+1) != NULL){
    }
    else{
        printf("Error: unable to get current working directory.\n");
        cwd[0]='\0';
    }
    return cwd;
}

bool change_dir(char* dir) {
    if (chdir(dir) != -1) {
        return true;
    } else {
        printf("[%s]: cannot change directory\n", dir);
        return false;
    }
}
