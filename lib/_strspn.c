#include "main.h"

/**
 * _strspn - returns the number of bytes in the initial segment of s which
 * consist only of bytes from accept
 * @s: a string
 * @accept: a prefix substring
 *
 * Return: number of bytes
 */
unsigned int _strspn(char *s, char *accept)
{
	unsigned int i, j, count = 0;

	for (i = 0; s[i] != '\0' && s[i] != ' '; i++)
		for (j = 0; accept[j] != '\0'; j++)
			if (s[i] == accept[j])
			{
				count++;
				break;
			}

	return (count);
}
