#include "headers.h"

int to_tokens(char* command, char TOKENS_2D);
bool is_builtin(int argn, char TOKENS_2D, const char* builtins[]);
char** expand_wildcard(int argn, char TOKENS_2D); 
void join_tokens(int argn, char TOKENS_2D, char* command);
