#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    char buf[INPUT_BUF_SIZE];
    char command[INPUT_BUF_SIZE];

    handle_signal(true);
    
    while(1) {
        shell_prompt(PS1);
        get_input(buf);
        bool is_bltin = parse_input(buf, command);
        if (is_bltin) {
            builtin_exec(command);
        } else {
            os_exec(command);
        }
    }

    return 0;
}
