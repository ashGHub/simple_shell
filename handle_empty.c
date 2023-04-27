#include "main.h"

/**
 * handle_empty - a function that handles empty command
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_empty(shell_t *shell)
{
	/* DO NOTHING FOR EMPTY COMMAND */
	free_string_array(shell->cmd_argv);
}
