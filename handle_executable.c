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
	char *full_path;

	full_path = _which(shell->cmd_argv[0], "PATH"); /* search PATH */
	if (full_path == NULL)
		full_path = _which(shell->cmd_argv[0], "PWD"); /* search PWD */
	if (full_path == NULL)
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: not found\n", shell->argv[0],
				shell->line_n, shell->cmd_argv[0]);
		free(full_path);
		free_string_array(shell->cmd_argv);
		return;
	}
	change_token(&shell->cmd_argv[0], full_path);
	cmd_pid = fork();
	if (cmd_pid == 0) /* Child proccess */
	{
		exec_status = execve((shell->cmd_argv)[0], shell->cmd_argv, environ);
		free(shell->cmd_argv[0]);
		if (exec_status < 0)
		{
			perror(shell->argv[0]);
			exit(1);
		}
	}
	else
	{
		wait(&status);
		free_string_array(shell->cmd_argv);
	}
}
