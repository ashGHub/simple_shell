#include "main.h"

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
