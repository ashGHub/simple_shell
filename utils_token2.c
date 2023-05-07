#include "main.h"

/**
 * argtok - break a command into arguments, it considers words
 *			in single quotes as a single argument
 * @cmd: command to be splitted
 * @save_ptr: pointer to be used maintain context between function calls
 *
 * Return: pointer to a null terminated argument, or NULL otherwise
 */
char *argtok(char *cmd, char **save_ptr)
{
	char *start = NULL, *p = NULL, state = 'D';

	if (cmd == NULL && save_ptr == NULL)
		return (NULL);
	start = cmd != NULL ? cmd : *save_ptr;
	if (start == NULL || *start == '\0')
		return (NULL);
	for (p = start; p && *p != '\0'; p++)
		switch (state)
		{
		case 'D': /* DULL */
			if (*p == '\'')
				state = 'S';
			else if (*p != ' ' && *p != '\t')
				state = 'W';
			start = p;
			break;
		case 'W': /* WORD */
			if (*p == '\'')
				state = 'S';
			else if (*p == ' ' || *p == '\t')
			{
				while (*p == ' ' || *p == '\t')
					*(p++) = '\0';
				*save_ptr = p;
				return (start);
			}
			break;
		case 'S': /* STRING */
			if (*p == '\'')
			{
				*save_ptr = p + 1;
				*(p - 1) = *p = '\0';
				return (start);
			}
			*(p - 1) = *p;
			break;
		}
	*save_ptr = p;
	return (start);
}

/**
 * count_args - counts total number of arguments in a command
 * @cmd: command
 *
 * Return: total number of arguments
 */
size_t count_args(char *cmd)
{
	size_t size = 0;
	char *cmd_arg = NULL, *cmd_cpy = NULL, *save_ptr = NULL;

	cmd_cpy = _strdup(cmd); /* FREE this */
	if (cmd_cpy == NULL)
		return (0);
	cmd_arg = argtok(cmd_cpy, &save_ptr);
	while (cmd_arg != NULL)
	{
		size++;
		cmd_arg = argtok(NULL, &save_ptr);
	}
	free(cmd_cpy);
	cmd_cpy = NULL;
	return (size);
}

/**
 * get_argv - build an argv, NULL terminated argument array for a given command
 * @cmd: command
 * Description: Given a command "echo 'Hello World'",
 *				it builds an argv ["echo", "Hello World", NULL]
 *
 * Return: a pointer to an argv, NULL otherwise
 */
char **get_argv(char *cmd)
{
	size_t size = 0, i = 0;
	char *cmd_arg = NULL, **cmd_argv = NULL, *save_ptr = NULL;
	char *cmd_cpy = NULL;

	if (cmd == NULL)
		return (NULL);
	cmd_cpy = _strdup(cmd); /*FREE this */
	if (cmd_cpy == NULL)
		return (NULL);
	size = count_args(cmd) + 1; /* 1 -> for NULL */
	cmd_argv = malloc(sizeof(char *) * size);
	if (cmd_argv == NULL)
		return (NULL);
	cmd_arg = argtok(cmd_cpy, &save_ptr);
	while (cmd_arg != NULL)
	{
		cmd_argv[i] = _strdup(cmd_arg);
		cmd_arg = argtok(NULL, &save_ptr);
		i++;
	}
	cmd_argv[i] = NULL;
	free(cmd_cpy);
	cmd_cpy = NULL;
	return (cmd_argv);
}
