#include "main.h"

/**
 * replace_variables - replaces variables in the cmd
 * @exit_status: exit status for the variable $?
 * @cmd: command
 *
 * Return: command with the variables replaced, NULL otherwise
 */
char *replace_variables(int exit_status, char *cmd)
{
	int i = 0, s = CMD_BUF_SIZE;
	char *cmd_buf = NULL, *c = NULL;
	char *var = NULL, *value = NULL, *v = NULL;
	char state = 'W'; /* W = WORD, V = VARIABLE */

	cmd_buf = malloc(sizeof(char) * s);
	if (cmd_buf == NULL)
		return (NULL);
	cmd_buf = _memset(cmd_buf, '\0', s); /* initialize heap allocation */
	c = cmd;
	while (c && *c != '\0')
	{
		switch (state)
		{
			case 'W':
				if (*c == '$')
					state = 'V';
				else
				{
					write_cmd_buf(*c, &cmd_buf, &i, &s);
					c++;
				}
				break;
			case 'V':
				c++;
				value = get_value(exit_status, &var, c);
				if (value != NULL)
					for (v = value; v && *v != '\0'; v++)
						write_cmd_buf(*v, &cmd_buf, &i, &s);
				c = c + _strlen(var);
				state = 'W';
				free(var);
				free(value);
				var = NULL;
				value = NULL;
				break;
		}
	}
	free(cmd);
	return (cmd_buf);
}

/**
 * write_cmd_buf - writes a character to the command buffer
 * @ch: character to be written on the command buffer
 * @c_buf: pointer to the command buffer
 * @i: pointer to the index of the command buffer
 * @s: pointer to the size of the of the command buffer
 *
 * Return: void
 */
void write_cmd_buf(char ch, char **c_buf, int *i, int *s)
{
	if (*i == *s - 1)
	{
		*c_buf = _realloc(*c_buf, *s, *s + CMD_BUF_SIZE);
		*s += CMD_BUF_SIZE;
	}
	(*c_buf)[(*i)++] = ch;
}

/**
 * get_value - determines the variable from the current position in
 *			the command and returns its value if the variable exists
 * @exit_status: exit status of the shell, needed for $? variable
 * @var_ptr: double pointer to store the variable being expanded
 * @c: pointer to the current position in the command
 *
 * Description: the function while determining the value stores the variable
 *				on the memory pointed by var_ptr in order to advance the
 *				position of c in the cmd string
 * Return: value of the variable if it exists, NULL otherwise
 */
char *get_value(int exit_status, char **var_ptr, char *c)
{
	char *str, *var_tmp, *value, *save_ptr = NULL;
	int pid = 0;

	if (c == NULL)
		return (NULL);
	str = _strdup(c);
	switch (*str)
	{
	case '$':
		var_tmp = "$";
		pid = getpid();
		value = _itoa(pid);
		break;
	case '?':
		var_tmp = "?";
		value = _itoa(exit_status);
		break;
	case ' ':
		var_tmp = " ";
		value = _strdup("$ ");
		break;
	case '\0':
		var_tmp = "";
		value = _strdup("$");
		break;
	default:
		var_tmp = _strtok_r(str, " $", &save_ptr);
		value = _strdup(_getenv_value(var_tmp));
		break;
	}
	*var_ptr = _strdup(var_tmp);
	free(str);
	return (value);
}

/**
 * _itoa - converts an integer to a string
 * @n: integer to be converted
 *
 * Return: string of n, or NULL otherwise
 */
char *_itoa(int n)
{
	int i, digits = 1, temp = n, is_neg = 0;
	char *num = NULL;

	for (temp /= 10; temp; temp /= 10)
		digits++;
	is_neg = n < 0 ? 1 : 0;
	if (is_neg)
		digits++;
	num = malloc(sizeof(char) * digits + 1); /* +1 for null byte */
	if (num == NULL)
		return (NULL);
	_memset(num, '\0', digits + 1); /* initialize heap allocation */
	for (temp = n, i = digits - 1; i >= 0; i--, temp /= 10)
		num[i] = (temp % 10) + '0';
	if (is_neg)
		num[0] = '-';
	return (num);
}

/**
 * remove_comment - removes comment from a cmd line
 * @cmd_line: cmd ine
 *
 * Return: pointer to altered cmd line, NULL otherwise
 */
char *remove_comment(char *cmd_line)
{
	char *cmnt = NULL;

	if (cmd_line == NULL)
		return (NULL);
	if (*cmd_line == '#')
		*cmd_line = '\0';
	cmnt = _strstr(cmd_line, " #");
	if (cmnt != NULL)
		*cmnt = '\0';
	cmnt = _strstr(cmd_line, ";#");
	if (cmnt != NULL)
		*cmnt = '\0';
	return (cmd_line);
}
