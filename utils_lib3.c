#include "main.h"

/**
 * _strcpy - copies the string src to dest, including the null character.
 * @src: source string
 * @dest: destination string
 *
 * Return: void
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	if (src == NULL || dest == NULL)
		return (dest);
	for (i = 0; *(src + i) != '\0'; i++)
		*(dest + i) = *(src + i);
	*(dest + i) = *(src + i);

	return (dest);
}

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes from source
 *
 * Return: destination string
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int i;

	for (i = 0; src[i] != '\0' && i < n; i++)
		dest[i] = src[i];

	for (; i < n; i++)
		dest[i] = '\0';

	return (dest);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: less than, greater than or equal to zero
 */
int _strcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);

	return (0);
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: destination string
 */
char *_strcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest && dest[i] != '\0'; i++)
		;
	for (j = 0; dest && src && src[j] != '\0'; i++, j++)
		dest[i] = src[j];
	if (dest)
		dest[i] = '\0';
	return (dest);
}

/**
 * _strncat - concatenates two strings
 * @dest: destination string
 * @src: source string
 * @n: number of bytes from source
 *
 * Return: destination string
 */
char *_strncat(char *dest, const char *src, int n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0' && j < n; i++, j++)
		dest[i] = src[j];

	if (dest[i] != '\0')
		dest[i] = '\0';

	return (dest);
}
