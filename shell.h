#include "headers.h"

void handle_signal(bool sig_ignored);
void shell_prompt(char* ps);
void get_input(char* buf_in);
bool parse_input(char* input, char* command);
void builtin_exec(char* command); 
void os_exec(char* command);
