#include "main.h"

/**
 * _atoi - converts a string into an integer
 * @s: a string
 *
 * Return: an integer
 */
int _atoi(char *s)
{
	unsigned int i, j, sign = 1, num = 0;

	for (i = 0; s[i] != '\0'; i++)
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] > 47 && s[i] < 58)
			break;
	/* If there are no numbers return 0 */
	if (s[i] == '\0')
		return (num);
	/* If there are numbers then return the number */
	for (j = i; s[j] > 47 && s[j] < 58; j++)
		num = (s[j] - '0') + num * 10;
	return (num * sign);
}

/**
 * _strlen - returns the length of a string
 * @s: a string
 *
 * Return: length of the string
 */
int _strlen(const char *s)
{
	int i, length = 0;

	if (s == NULL)
		return (0);
	for (i = 0; s[i] != '\0'; i++)
		length++;

	return (length);
}

/**
 * _strchr - locates a character in a string
 * @s: a string
 * @c: a character
 *
 * Return: pointer to the character in the string, or NULL otherwise
 */
char *_strchr(const char *s, char c)
{
	int i;

	if (s == NULL)
		return (NULL);
	for (i = 0; s[i] != '\0' && s[i] != c; i++)
		;
	if (c != '\0' && s[i] == '\0')
		return ('\0');
	return ((char *)&s[i]);
}

/**
 * _strstr - finds the first occurrence of the substring needle
 * in the string haystack
 * @haystack: a string
 * @needle: a substring
 *
 * Return: pointer to the first occurrence of the substring, NULL otherwise
 */
char *_strstr(const char *haystack, const char *needle)
{
	int i = 0, j = 0, k = 0;

	if (*needle == '\0')
		return ((char *)haystack);
	for (i = 0; haystack[i] != '\0'; i++)
	{
		for (j = 0, k = i; needle[j] != '\0' && haystack[k] != '\0'; j++, k++)
			if (haystack[k] != needle[j])
				break;
		if (needle[j] == '\0')
			break;
	}
	if (needle[j] == '\0' && haystack[i] != '\0')
		return ((char *)&haystack[i]);
	return ('\0');
}

/**
 * _strspn - returns the number of bytes in the initial segment of s which
 * consist only of bytes from accept
 * @s: a string
 * @accept: a prefix substring
 *
 * Return: number of bytes
 */
unsigned int _strspn(const char *s, const char *accept)
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

