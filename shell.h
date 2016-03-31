#include "headers.h"
#include <glob.h>

void handle_signal(bool sig_ignored);
void shell_prompt(char* ps);
void get_input(char* buf_in);
cmd_t parse_input(char* input, glob_t* globbuf);
void builtin_exec(glob_t* globbuf); 
void os_exec(glob_t* globbuf);
