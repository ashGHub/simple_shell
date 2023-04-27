#include "main.h"

/**
 * handle_setenv - initializes a new environemnt variable
 *				or modifies an existing one
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_setenv(shell_t *shell)
{
	int result;

	if (shell->cmd_argc != 3)
	{
		dprintf(2, "%s: Usage: setenv VARIABLE VALUE\n", shell->argv[0]);
		free_string_array(shell->cmd_argv);
		return;
	}
	result = _setenv(shell->cmd_argv[1], shell->cmd_argv[2]);
	if (result == -1)
		dprintf(2, "%s: setenv failed\n", shell->argv[0]);
	free_string_array(shell->cmd_argv);
}
