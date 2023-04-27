#include "main.h"

/**
 * _strchr - locates a character in a string
 * @s: a string
 * @c: a character
 *
 * Return: pointer to the character in the string, or NULL otherwise
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0' && s[i] != c; i++)
		;

	/**
	 * If c is not found return NULL
	 * But if c is also NULL,
	 * then return a pointer to the NULL character in the string
	 */
	if (c != '\0' && s[i] == '\0')
		return ('\0');

	/* If c is found return the address of the character */
	return (&s[i]);
}
