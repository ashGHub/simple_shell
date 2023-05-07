#include "main.h"

/**
 * main - a simple shell program
 * @ac: argument count of the shell program
 * @av: argument vector of the shell program
 * @ep: environment of the shell program
 *
 * Return: 0 on success, or 1 on error
 */
int main(int ac, char *av[], char *ep[])
{
	int i, inter_mode = 0, fd = STDIN_FILENO;
	char *prompt = "($) ", *line_delim = "\n";
	ssize_t read;
	shell_t shell;

	initialize_shell(&shell, ac, av, ep);
	if (ac >= 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			dprintf(STDERR_FILENO, "%s: %d: Can't open %s\n", av[0],
					shell.line_n, av[1]);
			shell.exit_status = CMD_NOT_FOUND;
			free_environ(&shell);
			return (shell.exit_status);
		}
	}
	else
		inter_mode = isatty(STDIN_FILENO);
	do {
		if (inter_mode)
		{
			write(STDOUT_FILENO, prompt, _strlen(prompt));
			fflush(stdout);
		}
		read = read_input(&shell.line_buf, &shell.line_size, fd);
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
	free_alias_list(shell.alias_head);
	return (shell.exit_status);
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
	shell->alias_head = NULL;
	shell->exit_status = 0;
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
	char *cmd_line = NULL, *cmd = NULL, *next_cmd = NULL;
	int argc, sep_ch = 0;

	cmd_line = shell->line_arr[i];
	cmd_line = remove_comment(cmd_line);
	cmd = parse_cmd(cmd_line, &next_cmd, &sep_ch);
	while (cmd != NULL)
	{
		cmd = substitute_alias(shell->alias_head, cmd);
		cmd = replace_variables(shell->exit_status, cmd);
		shell->cmd_argv = get_argv(cmd);
		argc = 0;
		while (shell->cmd_argv[argc] != NULL)
			argc++;
		shell->cmd_argc = argc;
		if (shell->cmd_argv[0] == NULL || *(shell->cmd_argv)[0] == '\0')
			handle = handle_empty;
		else
			handle = get_cmd_handler(shell->cmd_argv[0]);
		free(cmd);
		handle(shell);
		if (sep_ch == '&' && shell->exit_status != CMD_EXIT_SUCCESS)
			break;
		else if (sep_ch == '|' && shell->exit_status == CMD_EXIT_SUCCESS)
			break;
		cmd = parse_cmd(NULL, &next_cmd, &sep_ch);
	}
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
		{"env", handle_env},
		{"setenv", handle_setenv},
		{"unsetenv", handle_unsetenv},
		{"cd", handle_cd},
		{"alias", handle_alias},
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

/**
 * parse_cmd - parses the cmd line for command separator ;
 *			and the logical operators && and ||
 * @cmd_line: cmd line to be parsed
 * @next_cmd: pointer to the next cmd in the cmd line
 * @prev_opr_ch: pointer to hold the prev operator character used
 *
 * Return: pointer to the cmd in the cmd line, NULL on errors
 */
char *parse_cmd(char *cmd_line, char **next_cmd, int *prev_opr_ch)
{
	int i, is_non_sep = 0, is_non_opr = 0;
	char *start, *opr_ptr = NULL;
	char *sep = " ;&|", *opr = ";&|";

	if (cmd_line != NULL && *next_cmd == NULL)
		start = cmd_line;
	else
		start = *next_cmd;
	if (start == NULL || *start == '\0')
		return (NULL);
	/* skip sep chars until you find a non-sep char */
	while (start && *start != '\0')
	{
		is_non_sep = 1;
		for (i = 0; sep[i] != '\0'; i++)
			if (*start == sep[i])
			{
				is_non_sep = 0;
				break;
			}
		if (is_non_sep)
			break;
		start++;
	}
	/* start is now at a non-sep char, or on a null terminator */
	*next_cmd = _strpbrk(start, opr);
	while (*next_cmd && **next_cmd != '\0')
	{
		is_non_opr = 1;
		for (i = 0; opr[i] != '\0'; i++)
			if (**next_cmd == opr[i])
			{
				is_non_opr = 0;
				break;
			}
		if (is_non_opr)
			break;
		opr_ptr = (*next_cmd)++;
		*prev_opr_ch = *opr_ptr;
		*opr_ptr = '\0';
	}
	return (start);
}
