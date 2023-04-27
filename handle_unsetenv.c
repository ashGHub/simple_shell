#include "main.h"

/**
 * handle_unsetenv - initializes a new environemnt variable
 *				or modifies an existing one
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_unsetenv(shell_t *shell)
{
	int result;

	if (shell->cmd_argc != 2)
	{
		dprintf(2, "%s: Usage: unsetenv VARIABLE\n", shell->argv[0]);
		free_string_array(shell->cmd_argv);
		return;
	}
	result = _unsetenv(shell->cmd_argv[1]);
	if (result == -1)
		dprintf(2, "%s: unsetenv failed\n", shell->argv[0]);
	free_string_array(shell->cmd_argv);
}
