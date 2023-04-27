#include "main.h"

/**
 * _strtok_r - a function that break a string into a sequence of 0 or more
 *			non empty tokens. An implementation of the strtok_r() function.
 * @str: string to be splitted
 * @delim: string that contains delimiters
 * @save_ptr: pointer to char * used to maintain context between function calls
 *
 * Return: pointer to a null terminated token, or NULL otherwise
 */
char *_strtok_r(char *str, const char *delim, char **save_ptr)
{
	int i, is_non_delim = 0;
	char *start, *delim_ptr = NULL;

	if (delim == NULL || (str == NULL && save_ptr == NULL))
		return (NULL);
	if (str != NULL && *save_ptr == NULL)
		start = str;
	else
		start = *save_ptr;
	if (start == NULL || *start == '\0')
		return (NULL);
	while (start && *start != '\0')
	{
		is_non_delim = 1;
		for (i = 0; delim[i] != '\0'; i++)
			if (*start == delim[i])
			{
				is_non_delim = 0;
				break;
			}
		if (is_non_delim)
			break;
		start++;
	}
	*save_ptr = _strpbrk(start, delim);
	while (*save_ptr && **save_ptr != '\0')
	{
		is_non_delim = 1;
		for (i = 0; delim[i] != '\0'; i++)
			if (**save_ptr == delim[i])
			{
				is_non_delim = 0;
				break;
			}
		if (is_non_delim)
			break;
		delim_ptr = (*save_ptr)++;
		*delim_ptr = '\0';
	}
	return (start);
}

/**
 * get_tokens - build a token string array for given string delimiter
 * @str: string
 * @delim: delimiter string
 * Description: Given a string "/bin/ls -l" and a delimiter space,
 *              it builds a string array ["/bin/ls", "-l", NULL]
 *
 * Return: a pointer to a token string array
 */
char **get_tokens(char *str, char *delim)
{
	char *token, **token_array, *save_ptr = NULL;
	int size, i = 0;
	char *str_cpy = NULL;

	/* this is because strtok modifies */
	/* the original string */
	str_cpy = malloc(sizeof(char) * (_strlen(str) + 1)); /*FREE this */
	str_cpy = _strcpy(str_cpy, str);
	size = count_tokens(str, delim) + 1; /* 1 -> for NULL */
	token_array = malloc(sizeof(char *) * size);
	token = _strtok_r(str_cpy, delim, &save_ptr);
	while (token)
	{
		token_array[i] = malloc_token(token);
		token = _strtok_r(NULL, delim, &save_ptr);
		i++;
	}
	token_array[i] = NULL;
	free(str_cpy);
	str_cpy = NULL;
	return (token_array);
}

/**
 * count_tokens - counts total tokens in a string
 * @str: string
 * @delim: delimiter string
 *
 * Return: total word counts
 */
short count_tokens(char *str, char *delim)
{
	short size = 0;
	char *token, *str_cpy = NULL, *save_ptr = NULL;

	/* this is because strtok modifies */
	/* the original string */
	str_cpy = malloc(sizeof(char) * (_strlen(str) + 1)); /* FREE this */
	str_cpy = _strcpy(str_cpy, str);
	token = _strtok_r(str_cpy, delim, &save_ptr);
	while (token)
	{
		size++;
		token = _strtok_r(NULL, delim, &save_ptr);
	}
	free(str_cpy);
	str_cpy = NULL;
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
	char *new_token = NULL;

	new_token = malloc(sizeof(char) * (_strlen(token) + 1));
	_strcpy(new_token, token);
	return (new_token);
}

/**
 * change_token - a function that changes a token to another
 * @old_token: the old token
 * @new_token: the new token
 *
 * Return: void
 */
void change_token(char **old_token, char *new_token)
{
	free(*old_token);
	*old_token = new_token;
}
