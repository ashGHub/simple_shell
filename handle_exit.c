#include "main.h"

/**
 * handle_exit - handles exit command
 * @cmd: command for the program with its options
 */
void handle_exit(char **cmd)
{
	free(cmd);
	exit(0);
}
