#include "main.h"

/**
 * free_cmd - free a command array memory allocation
 * @cmd: command array
 */
void free_cmd(char **cmd)
{
	int i;

	for (i = 0; cmd && cmd[i]; i++)
		free(cmd[i]);
	free(cmd);
}

/**
 * build_cmd - build a command from a given command string
 * @str: command string
 *
 * Description: Given a string "/bin/ls -l",
 *              it builds a command array ["/bin/ls", "-l", NULL]
 *
 * Return: a pointer to a command with its options
 */
char **build_cmd(char *str)
{
	char *space_delimiter = " ";
	char *token, **result;
	int size, i = 0;

	size = count_word(str) + 1;
	result = malloc(sizeof(char *) * size);
	token = strtok(str, space_delimiter);
	while (token)
	{
		result[i] = malloc_token(token);
		token = strtok(NULL, " ");
		i++;
	}
	result[i] = NULL;
	return (result);
}

/**
 * count_word - counts total words in a string
 * @str: string
 *
 * Return: total word counts
 */
short count_word(char *str)
{
	short size = 0;
	char *token, *str_cpy;

    /* this is because strtok modifies */
	/* the original string */
	str_cpy = malloc(sizeof(char) * strlen(str));
	str_cpy = strcpy(str_cpy, str);
	token = strtok(str_cpy, " ");
	while (token)
	{
		size++;
		token = strtok(NULL, " ");
	}
	return (size);
}

/**
 * malloc_token - allocate token a memory
 * @token: string
 *
 * Return: pointer to the allocated token memory
 */
char *malloc_token(char *token)
{
	char *cmd;

	cmd = malloc(sizeof(char) * strlen(token));
	strcpy(cmd, token);
	/* trim newline */
	cmd[strcspn(cmd, "\n")] = '\0';
	return (cmd);
}
