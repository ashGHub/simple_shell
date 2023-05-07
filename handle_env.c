#include "main.h"

/**
 * handle_env - runs builtin command env, that prints the current environment
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_env(shell_t *shell)
{
	int i;

	(void)shell;
	for (i = 0; environ[i] != NULL; i++)
		_puts(environ[i]);
	free_string_array(shell->cmd_argv);
	shell->exit_status = EXIT_SUCCESS;
}
