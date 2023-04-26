#include "main.h"

/**
 * handle_system_call - runs system programs with child process
 * @cmd: command for the program with its options
 */
void handle_system_call(char **cmd)
{
	pid_t cmd_pid;
	int status;

	cmd_pid = fork();
	if (cmd_pid == 0)
	{
		if (execve(cmd[0], cmd, NULL) < 0)
		{
			perror("Error");
			exit(1);
		}
	}
	else
	{
		wait(&status);
		free_cmd(cmd);
	}
}
