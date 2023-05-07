#include "main.h"

int main(void)
{
	char *my_line = NULL;
	size_t my_n = 0;
	int my_read = 0, init_mode;

	init_mode = isatty(STDIN_FILENO);
	printf("init_mode: %d\n", init_mode);
	if (init_mode)
	{
		printf("my get$ ");
		fflush(stdout);
	}
	my_read = read_input(&my_line, &my_n, stdin);
	printf("my read: %d\n", my_read);
	if (my_line != NULL)
		printf("line: \"%s\"\n", my_line);
	free(my_line);
	return (0);
}
