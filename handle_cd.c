#include "main.h"

/**
 * handle_cd - a function that handles cd command
 * @shell: the shell input data
 *
 * Return: void
 */
void handle_cd(shell_t *shell)
{
	char *cur_path, *given_path, *old_path, *path;
	int cd_stat;

	given_path = shell->cmd_argv[1];
	if (given_path == NULL || _strcmp(given_path, "~") == 0) /* cd $HOME */
		path = _getenv_value("HOME");
	else if (_strcmp(given_path, "-") == 0) /* cd - */
		path = _getenv_value("OLDPWD");
	else
		path = given_path; /*cd [DIRECTORY] */
	old_path = _getenv_value("PWD");
	cd_stat = chdir(path);
	if (cd_stat == -1)
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: cant't cd to %s\n", shell->argv[0],
				shell->line_n, shell->cmd_argv[0], path);
		free_string_array(shell->cmd_argv);
		return;
	}
	cur_path = getcwd(NULL, 0);
	if (cur_path == NULL)
	{
		dprintf(STDERR_FILENO, "%s: %d: %s: cant't cd to %s\n", shell->argv[0],
				shell->line_n, shell->cmd_argv[0], path);
		free_string_array(shell->cmd_argv);
		return;
	}
	_setenv("OLDPWD", old_path);
	_setenv("PWD", cur_path);
	free(cur_path);
	free_string_array(shell->cmd_argv);
}
