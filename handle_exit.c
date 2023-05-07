#include "main.h"

/**
 * handle_exit - handles exit command
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_exit(shell_t *shell)
{
	int i, status;
	char *cmd_ptr = shell->cmd_argv[1];

	for (i = 0; cmd_ptr && cmd_ptr[i] != '\0'; i++)
		if (!_isdigit(cmd_ptr[i]))
		{
			dprintf(STDERR_FILENO, "%s: %d: exit: Illegal number: %s\n", shell->argv[0],
					shell->line_n, shell->cmd_argv[1]);
			free_string_array(shell->cmd_argv);
			shell->exit_status = CMD_EXIT_FAILURE;
			return;
		}
	if (shell->cmd_argv[1] != NULL)
		status = _atoi(shell->cmd_argv[1]);
	else
		status = shell->exit_status;
	free_shell(shell);
	exit(status);
}
