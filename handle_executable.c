#include "main.h"

/**
 * handle_executable - runs executable program with child process and
 *					if the executable program is not found it prints
 *					an error message to stderr
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_executable(shell_t *shell)
{
	pid_t cmd_pid;
	int status, exec_status = 0;
	char *full_path = NULL;

	full_path = _which(shell->cmd_argv[0]);
	if (full_path == NULL)
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", shell->argv[0],
				shell->line_n, shell->cmd_argv[0]);
		free_string_array(shell->cmd_argv);
		shell->exit_status = CMD_NOT_FOUND;
		return;
	}
	cmd_pid = fork();
	if (cmd_pid == 0) /* Child proccess */
	{
		exec_status = execve(full_path, shell->cmd_argv, environ);
		free(shell->cmd_argv[0]);
		free(full_path);
		if (exec_status < 0)
		{
			perror(shell->argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		free(full_path);
		free_string_array(shell->cmd_argv);
		shell->exit_status = WEXITSTATUS(status);
	}
}
