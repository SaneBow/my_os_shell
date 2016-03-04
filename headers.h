#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#define TOKENS_2D tokens[MAX_ARGS_NUM][INPUT_BUF_SIZE]
#define INPUT_BUF_SIZE 255
#define MAX_ARGS_NUM 255
#define PS1 "3150 shell"
typedef enum {false, true} bool;
typedef enum {CMD_BLANK, CMD_BUILTIN, CMD_OS} cmd_t;
bool HAS_PROMPT;

#endif
