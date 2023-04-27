#include "main.h"

/**
 * handle_exit - handles exit command
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_exit(shell_t *shell)
{
	int status;

	if (shell->cmd_argv[1] != NULL)
		status = _atoi(shell->cmd_argv[1]);
	else
		status = 0;
	free_shell(shell);
	exit(status);
}
