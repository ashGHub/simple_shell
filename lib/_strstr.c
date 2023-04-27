#include "main.h"

/**
 * _strstr - finds the first occurrence of the substring needle
 * in the string haystack
 * @haystack: a string
 * @needle: a substring
 *
 * Return: pointer to the first occurrence of the substring, NULL otherwise
 */
char *_strstr(char *haystack, char *needle)
{
	int i = 0, j = 0, k = 0;

	if (*needle == '\0')
		return (haystack);

	for (i = 0; haystack[i] != '\0'; i++)
	{
		for (j = 0, k = i; needle[j] != '\0' && haystack[k] != '\0'; j++, k++)
			if (haystack[k] != needle[j])
				break;
		if (needle[j] == '\0')
			break;
	}

	if (needle[j] == '\0' && haystack[i] != '\0')
		return (&haystack[i]);

	return ('\0');
}
