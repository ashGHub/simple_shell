#include "main.h"

/**
 * main - testing argtok function
 *
 * Return: 0 on success, or 1 on error
 */
int main(void)
{
	char str[] = "ls                                              ", *save_ptr = NULL, *arg;
	int i = 0, j = 0;

	arg = argtok(str, &save_ptr);	
	while (arg != NULL)
	{
		printf("arg[%d]:", i++);
		for (j = 0; arg[j] != '\0'; j++)
		{
			if (arg[j] == ' ')
				putchar('*');
			else
				putchar(arg[j]);
		}
		putchar('\n');
		arg = argtok(NULL, &save_ptr);
	}
	return (0);
}
