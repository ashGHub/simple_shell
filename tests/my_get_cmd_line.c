#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * read_input - a function that reads the whole input from a file stream
 * @line_buf: buffer fo the input
 * @size: size of the memory pointed by *line_buf
 * @stream: stream to get input from
 *
 * Return: number of characters read, or -1 on error
 */
ssize_t read_input(char **line_buf, size_t *size, FILE *stream)
{
	ssize_t bytes = 0;
	size_t i, buffer_size = 1024, read_bytes;
	int fd, inter_mode;
	char *nl_ptr = NULL;

	if (line_buf == NULL || size == NULL || stream == NULL)
		return (-1);
	if ((*line_buf == NULL && *size == 0) || *size <= buffer_size)
	{
		*line_buf = _realloc(*line_buf, *size, buffer_size);
		*size = buffer_size;
		if (*line_buf == NULL)
			return (-1);
		for (i = 0; i < buffer_size; i++)
			(*line_buf)[i] = '\0';
	}
	fd = fileno(stream);
	inter_mode = isatty(fd);
	do {
		read_bytes = read(fd, *line_buf + bytes, buffer_size - 1);
		if (read_bytes == buffer_size - 1)
		{
			*line_buf = _realloc(*line_buf, *size, (*size + buffer_size));
			*size += buffer_size;
			if (*line_buf == NULL)
				return (-1);
		}
		/* In interactive mode, read only until a newline */
		nl_ptr = _strchr(*line_buf, '\n');
		if (fd == STDIN_FILENO && nl_ptr != NULL && inter_mode)
		{
			bytes = ++nl_ptr - (*line_buf);
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
	my_read = read_input(&my_line, &my_n, stdin);
	printf("my read: %d\n", my_read);
	if (my_line != NULL)
		printf("line: \"%s\"\n", my_line);
	free(my_line);
	return (0);
}
