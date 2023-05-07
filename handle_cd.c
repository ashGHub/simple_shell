#include "main.h"

int cd_home(void);
int cd_back(void);
int cd_path(char *given_path);

/**
 * handle_cd - a function that handles cd command
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_cd(shell_t *shell)
{
	char *old_path = NULL, *cur_path = NULL, *given_path = NULL;
	int cd_stat;

	given_path = shell->cmd_argv[1];
	/* Get the old path */
	old_path = getcwd(NULL, 0);
	if (old_path == NULL)
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: can't cd to %s\n", shell->argv[0],
				shell->line_n, shell->cmd_argv[0], given_path);
		free(old_path);
		free_string_array(shell->cmd_argv);
		shell->exit_status = CMD_EXIT_FAILURE;
		return;
	}
	/* Change directory */
	if (given_path == NULL || _strcmp(given_path, "~") == 0) /* cd $HOME */
		cd_stat = cd_home();
	else if (_strcmp(given_path, "-") == 0) /* cd - */
		cd_stat = cd_back();
	else
		cd_stat = cd_path(given_path);
	if (cd_stat == -1)
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: can't cd to %s\n", shell->argv[0],
				shell->line_n, shell->cmd_argv[0], given_path);
		free(old_path);
		free_string_array(shell->cmd_argv);
		shell->exit_status = CMD_EXIT_FAILURE;
		return;
	}
	/* Get the current path */
	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: can't cd to %s\n", shell->argv[0],
				shell->line_n, shell->cmd_argv[0], given_path);
		free_string_array(shell->cmd_argv);
		shell->exit_status = CMD_EXIT_FAILURE;
		return;
	}
	if (given_path && _strcmp(given_path, "-") == 0)
		_puts(cur_path);
	_setenv("OLDPWD", old_path);
	_setenv("PWD", cur_path);
	free(old_path);
	free(cur_path);
	free_string_array(shell->cmd_argv);
	shell->exit_status = CMD_EXIT_SUCCESS;
}

/**
 * cd_home - changes directory to HOME
 *
 * Return: 0 on success, or -1 on error
 */
int cd_home(void)
{
	char *dest_path = NULL;
	int cd_stat;

	dest_path = _getenv_value("HOME");
	if (dest_path == NULL)
		return (0);
	cd_stat = chdir(dest_path);
	return (cd_stat);
}

/**
 * cd_back - changes directory back to OLDPWD
 *
 * Return: 0 on success, or -1 on error
 */
int cd_back(void)
{
	char *dest_path = NULL;
	int cd_stat;

	dest_path = _getenv_value("OLDPWD");
	if (dest_path == NULL)
		return (0);
	cd_stat = chdir(dest_path);
	return (cd_stat);
}

/**
 * cd_path - changes directory to the given path
 * @given_path: given path to cd
 *
 * Return: 0 on success, or -1 on error
 */
int cd_path(char *given_path)
{
	int cd_stat;

	cd_stat = chdir(given_path);
	return (cd_stat);
}
