#include "shell.h"
#include <stdio.h>
#include <stdlib.h>


int main() {

    char buf[INPUT_BUF_SIZE];
    glob_t expanded_cmd;

    handle_signal(true);
    
    while(1) {
        shell_prompt(PS1);
        get_input(buf);
        cmd_t cmd_type = parse_input(buf, &expanded_cmd);
        switch (cmd_type) {
            case CMD_BLANK:
                break;
            case CMD_BUILTIN: 
                builtin_exec(&expanded_cmd);
                break;
            case CMD_OS:
                os_exec(&expanded_cmd);
                break;
        }
    }

    return 0;
}
