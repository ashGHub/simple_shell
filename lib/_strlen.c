#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: a string
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
	int i, length = 0;

	for (i = 0; s[i] != '\0'; i++)
		length++;

	return (length);
}
