#include "main.h"

/**
 * _strpbrk - locates the first occurrence in the string s of
 * any of the bytes in accept.
 * @s: a string
 * @accept: search key string
 *
 * Return: pointer to the found character in the string s, NULL otherwise
 */
char *_strpbrk(char *s, char *accept)
{
	int i, j, found = 0;

	for (i = 0; s[i] != '\0' && !found; i++)
		for (j = 0; accept[j] != '\0' && !found; j++)
			if (s[i] == accept[j])
				found = 1;
	i--;
	if (s[i] != '\0' && found)
		return (&s[i]);

	return ('\0');
}
