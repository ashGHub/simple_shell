#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	char *get_line = NULL;
	size_t get_n = 0;
	int get_read = 0, init_mode;

	init_mode = isatty(STDIN_FILENO);
	printf("init_mode: %d\n", init_mode);
	if (init_mode)
	{
		printf("std_get$ ");
		fflush(stdout);
	}
	get_read = getline(&get_line, &get_n, stdin);
	printf("get read: %d\n", get_read);
	if (get_line != NULL)
		printf("line: \"%s\"\n", get_line);
	free(get_line);
	return (0);
}
