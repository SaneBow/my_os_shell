#include "headers.h"
#include <glob.h>

void handle_signal(bool sig_ignored);
void shell_prompt(char* ps);
void get_input(char* buf_in);
bool parse_input(char* input, char* command, glob_t* globbuf);
void builtin_exec(char* command); 
void os_exec(glob_t* globbuf);
