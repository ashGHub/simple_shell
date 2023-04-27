#include "main.h"

/**
 * main - a simple shell program
 * @ac: argument count of the shell program
 * @av: argument vector of the shell program
 * @ep: environment of the shell program
 *
 * Return: 0 on success, or 1 on error
 */
int main(int ac __attribute__((unused)), char *av[] __attribute__((unused)),
		char *ep[] __attribute__((unused)))
{
	int i, inter_mode;
	char *line_delim = ";\n";
	ssize_t read;
	shell_t shell;

	initialize_shell(&shell, ac, av, ep);
	inter_mode = isatty(STDIN_FILENO);
	do {
		if (inter_mode)
		{
			printf("$ ");
			fflush(stdout);
		}
		read = read_input(&shell.line_buf, &shell.line_size, stdin);
		shell.line_arr = get_tokens(shell.line_buf, line_delim);
		for (i = 0; read != EOF && shell.line_arr[i] != NULL; i++)
		{
			shell.line_n++;
			execute_cmd(&shell, i);
		}
		free_line(&shell);
	} while (read != EOF);
	if (read == EOF && inter_mode)
		_putchar('\n');
	free_environ(&shell);
	return (EXIT_SUCCESS);
}

/**
 * initialize_shell - a function that initializes the shell data
 * @shell: pointer to the shell data structure
 * @ac: argument count of the shell program
 * @av: argument vector of the shell program
 * @ep: environment of the shell program
 *
 * Return: void
 */
void initialize_shell(shell_t *shell, int ac, char **av, char **ep)
{
	int i, env_size = 0;

	shell->argc = ac;
	shell->argv = av;
	shell->envp = ep;
	shell->line_buf = NULL;
	shell->line_size = 0;
	shell->line_arr = NULL;
	shell->line_n = 0;
	shell->cmd_argc = 0;
	shell->cmd_argv = NULL;
	env_size = 0;
	while (ep[env_size] != NULL)
		env_size++;
	environ = malloc(sizeof(char *) * (env_size + 1));
	for (i = 0; i < env_size; i++)
		environ[i] = _strdup(ep[i]);
	environ[i] = NULL;
}

/**
 * execute_cmd - executes a command
 * @shell: shell input data
 * @i: cmd line array index
 *
 * Return: void
 */
void execute_cmd(shell_t *shell, int i)
{
	void (*handle)(shell_t *);
	char *delimiter = " \t\n";
	int argc;

	shell->cmd_argv = get_tokens(shell->line_arr[i], delimiter);
	argc = 0;
	while (shell->cmd_argv[argc] != NULL)
		argc++;
	shell->cmd_argc = argc;
	if (shell->cmd_argv[0] == NULL || *(shell->cmd_argv)[0] == '\0')
		handle = handle_empty;
	else
		handle = get_cmd_handler(shell->cmd_argv[0]);
	handle(shell);
}

/**
 * get_cmd_handler - a function to get the appropriate command handler
 * @cmd: command value
 *
 * Return: pointer to the command handling function
 *         default to system call
 */
void (*get_cmd_handler(char *cmd))(shell_t *)
{
	int i = 0, hasHandler = 0;
	cmd_handler_t cmd_handlers[] = {
		{"exit", handle_exit},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv},
		{"cd", handle_cd},
		{NULL, handle_executable}
	};

	while (cmd_handlers[i].cmd)
	{
		hasHandler = _strcmp(cmd_handlers[i].cmd, cmd) == 0;
		if (hasHandler)
			break;
		i++;
	}
	return (cmd_handlers[i].handle);
}
