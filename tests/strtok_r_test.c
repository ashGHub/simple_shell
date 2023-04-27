#include "main.h"

/**
 * main - a program that tests the strtok_r function
 *
 * Return: void
 */
int main(int argc, char *argv[])
{
	int i, arg_i;
	char **words, *delim = " \n";

	for (arg_i = 1; arg_i < argc; arg_i++)
	{
		words = get_tokens(argv[arg_i], delim);
		printf("--------------------------------------------------\n");
		for (i = 0; words[i] != NULL; i++)
			printf("Token[%d]: %s\n", i + 1, words[i]);
		printf("--------------------------------------------------\n");
		for (i = 0; words[i] != NULL; i++)
			free(words[i]);
		free(words);
	}
	return (0);
}