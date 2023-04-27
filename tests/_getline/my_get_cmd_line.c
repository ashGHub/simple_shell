#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * _getline - my implementation of getline function
 * @line_ptr: pointer to memory, to put the line in
 * @n: size of the memory pointed by *line_ptr
 * @stream: stream to get line from
 *
 * Return: number of characters read, or -1 on error
 */
ssize_t get_cmd_line(char **line_ptr, size_t *n, FILE *stream)
{
	ssize_t bytes = 0;
	size_t i, buffer_size = 1024, read_bytes;
	int fd, init_mode;
	char *nl_ptr = NULL;

	if (line_ptr == NULL || n == NULL || stream == NULL)
		return (-1);
	if ((*line_ptr == NULL && *n == 0) || *n <= buffer_size)
	{
		*n = buffer_size;
		*line_ptr = realloc(*line_ptr, *n);
		if (*line_ptr == NULL)
			return (-1);
		for (i = 0; i < buffer_size; i++)
			(*line_ptr)[i] = '\0';
	}
	fd = fileno(stream);
	init_mode = isatty(fd);
	do
	{
		read_bytes = read(fd, *line_ptr + bytes, buffer_size - 1);
		if (read_bytes == buffer_size - 1)
		{
			*n += buffer_size;
			*line_ptr = realloc(*line_ptr, *n);
			if (*line_ptr == NULL)
				return (-1);
		}
		nl_ptr = strchr(*line_ptr, '\n');
		if (fd == STDIN_FILENO && nl_ptr != NULL && init_mode)
		{
			bytes = ++nl_ptr - (*line_ptr);
			*nl_ptr = '\0';
			return (bytes);
		}
		bytes += read_bytes;
	} while (read_bytes != 0);
	if (bytes == 0)
		return (EOF);
	return (bytes);
}

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
	my_read = get_cmd_line(&my_line, &my_n, stdin);
	printf("my read: %d\n", my_read);
	if (my_line != NULL)
		printf("line: \"%s\"\n", my_line);
	free(my_line);
	return (0);
}
