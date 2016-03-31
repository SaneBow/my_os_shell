#include "headers.h"
#include <glob.h>

int to_tokens(char* command, char TOKENS_2D);
bool is_builtin(int argn, char TOKENS_2D, const char* builtins[]);
void expand_wildcard(int argn, char TOKENS_2D,glob_t* globbuf); 
void join_tokens(int argn, char TOKENS_2D, char* command);
