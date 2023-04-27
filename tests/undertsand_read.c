#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char line[10] = {0};
	int i, total_read = 0, inter_mode;

	inter_mode = isatty(STDIN_FILENO);
	printf("inter_mode: %d\n", inter_mode);
	if (inter_mode)
	{
		printf("(eyob721$) ");
		fflush(stdout);
	}
	total_read = read(STDIN_FILENO, line, 10);
	printf("Total read: %d\n", total_read);
	for (i = 0; i < 10; i++)
	{
		if (line[i] == '\n')
			printf("line[%d]: \\n\n", i);
		else if (line[i] == '\0')
			printf("line[%d]: \\0\n", i);
		else
			printf("line[%d]: %c\n", i, line[i]);
	}
	printf("Line: %s", line);
	return (0);
}
