#include "main.h"

/**
 * _strdup - a function that duplicates a given str, using malloc
 * similar to the function strdup, in the standard library
 * @str: a given string
 *
 * Return: pointer to the duplicated memory
 */
char *_strdup(char *str)
{
	int i, len = 0;
	char *dup;

	if (str == NULL)
		return (NULL);

	for (i = 0; *(str + i) != '\0'; i++)
		len++;
	len++;

	dup = malloc(sizeof(char) * len);

	if (dup)
		for (i = 0; i < len; i++)
			*(dup + i) = *(str + i);

	return (dup);
}
