#include "main.h"

/**
 * handle_alias - handles builtin alias command
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_alias(shell_t *shell)
{
	int i, stat = CMD_EXIT_SUCCESS;
	char *arg = NULL;

	if (shell->cmd_argc == 1)
	{
		print_alias_list(shell->alias_head);
		shell->exit_status = stat;
	}
	else
		for (i = 1; shell->cmd_argv[i] != NULL; i++)
		{
			arg = shell->cmd_argv[i];
			if (*arg != '=' && _strchr(arg, '=') != NULL)
			{
				stat = add_alias_node(&shell->alias_head, arg);
				if (stat == CMD_ALIAS_FAILURE)
					perror(shell->argv[0]);
			}
			else
			{
				stat = print_alias_node(shell->alias_head, arg);
				if (stat == CMD_ALIAS_FAILURE)
					dprintf(STDERR_FILENO, "alias: %s not found\n", arg);
			}
			if (stat != CMD_EXIT_SUCCESS)
				shell->exit_status = stat;
		}
	free_string_array(shell->cmd_argv);
}
