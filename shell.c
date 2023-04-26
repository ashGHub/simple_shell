#include "main.h"

/**
 * main - a super simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line;
	size_t len;
	ssize_t read;

	do {
		printf("$ ");
		read = getline(&line, &len, stdin);
		if (read != EOF)
			exec_cmd(line);
	} while (read != EOF);
	free(line);
	return (0);
}

/**
 * exec_cmd - executes a command
 * @str: command string
 */
void exec_cmd(char *str)
{
	void (*handle)(char **);
	char **cmd;

	cmd = build_cmd(str);
	handle = get_cmd_handler(cmd[0]);
	handle(cmd);
}

/**
 * get_cmd_handler - a function to get the appropriate command handler
 * @cmd: command value
 *
 * Return: pointer to the command handling function
 *         default to system call
 */
void (*get_cmd_handler(char *cmd))(char **)
{
	command_t cmd_handlers[] = {
		{"exit", handle_exit},
		{NULL, handle_system_call}
	};
	int idx = 0, hasHandler = 0;

	while (cmd_handlers[idx].value)
	{
		hasHandler = strcmp(cmd_handlers[idx].value, cmd) == 0;
		if (hasHandler)
			break;
		idx++;
	}
	return (cmd_handlers[idx].handle);
}
