#include "headers.h"

#define BUILTIN_NUM 2
const char* BUILTIN_LIST[BUILTIN_NUM];

void builtin(char* func, char args[][INPUT_BUF_SIZE], int argn);
