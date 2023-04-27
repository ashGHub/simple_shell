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

