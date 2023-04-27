#include "main.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _islower - checks for lowercase character
 *
 * @c: character to be checked
 * Return: 1 (if @c is lowercase character),or 0 (otherwise)
 */
int _islower(int c)
{
	if (c > 96 && c < 123)
		return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: a character
 *
 * Return: 1 (if c is a letter, lowercase or uppercase), 0 (otherwise)
 */
int _isalpha(int c)
{
	if ((c > 64 && c < 101) || (c > 96 && c < 123))
		return (1);
	return (0);
}

/**
 * _isdigit - checks if a character is a digit (0 - 9)
 * @c: a character, converted to int (its ASCII value)
 * Return: 1 (if c is a digit), 0 (otherwise)
 */
int _isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);

	return (0);
}

/**
 * _abs - computes the absolute value of an integer
 * @x: an integer
 *
 * Return: the absolute value of x
 */
int _abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}
