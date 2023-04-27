#include "main.h"

/**
 * _strdup - a function that duplicates a given str, using malloc
 * similar to the function strdup, in the standard library
 * @str: a given string
 *
 * Return: pointer to the duplicated memory
 */
char *_strdup(const char *str)
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

/**
 * _strpbrk - locates the first occurrence in the string s of
 * any of the bytes in accept.
 * @s: a string
 * @accept: search key string
 *
 * Return: pointer to the found character in the string s, NULL otherwise
 */
char *_strpbrk(const char *s, const char *accept)
{
	int i, j, found = 0;

	for (i = 0; s[i] != '\0' && !found; i++)
		for (j = 0; accept[j] != '\0' && !found; j++)
			if (s[i] == accept[j])
				found = 1;
	i--;
	if (s[i] != '\0' && found)
		return ((char *)&s[i]);

	return ('\0');
}

/**
 * _memcpy - copies n bytes from memory area src to memory area dest
 * @dest: destination memory area
 * @src: source memory area
 * @n: number of bytes
 *
 * Return: destination memory area
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _memset - fills the first n bytes of memory pointed by s
 * with a constant byte b
 * @s: memory location
 * @n: number of bytes
 * @b: a constant byte
 *
 * Return: memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;

	return (s);
}
