#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * struct command - a structure for command handler
 * @value: command string
 * @handle: a function for handling the command
 *
 * Description: this a structure for handling commands
 */
typedef struct command
{
	char *value;
	void (*handle)(char **);
} command_t;

char *malloc_token(char *token);
short count_word(char *str);

void free_cmd(char **cmd);
char **build_cmd(char *str);
void exec_cmd(char *str);

void handle_system_call(char **cmd);
void handle_exit(char **cmd);
void (*get_cmd_handler(char *cmd))(char **);

#endif
