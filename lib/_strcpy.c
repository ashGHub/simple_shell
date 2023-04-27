#include "main.h"

/**
 * _strcpy - copies the string src to dest, including the null character.
 * @src: source string
 * @dest: destination string
 *
 * Return: void
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; *(src + i) != '\0'; i++)
		*(dest + i) = *(src + i);
	*(dest + i) = *(src + i);

	return (dest);
}

