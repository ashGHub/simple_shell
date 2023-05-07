#include "main.h"

/**
 * read_input - a function that reads the whole input from a file stream
 * @line_buf: buffer fo the input
 * @size: size of the memory pointed by *line_buf
 * @fd: file descriptor of the file to get input from
 *
 * Return: number of characters read, or -1 on error
 */
ssize_t read_input(char **line_buf, size_t *size, int fd)
{
	ssize_t bytes = 0;
	size_t read_bytes;
	int inter_mode;
	char buffer[LINE_BUF_SIZE] = {0}, *nl_ptr = NULL;

	if (line_buf == NULL || size == NULL || fd == -1)
		return (-1);
	if ((*line_buf == NULL && *size == 0) || *size <= LINE_BUF_SIZE)
	{
		*line_buf = _realloc(*line_buf, *size, LINE_BUF_SIZE);
		*size = LINE_BUF_SIZE;
		if (*line_buf == NULL)
			return (-1);
	}
	inter_mode = isatty(STDIN_FILENO);
	do {
		read_bytes = read(fd, buffer, LINE_BUF_SIZE - 1);
		buffer[read_bytes] = '\0';
		_strcpy(*line_buf + bytes, buffer);
		if (read_bytes >= (LINE_BUF_SIZE - 1) / 2)
		{
			*line_buf = _realloc(*line_buf, *size, (*size + LINE_BUF_SIZE));
			*size += LINE_BUF_SIZE;
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

/**
 * concat_strings - concatenates three strings
 * @str1: first string
 * @str2: second string
 * @str3: third string
 *
 * Return: pointer to appended path, or NULL on errors
 */
char *concat_strings(const char *str1, const char *str2, const char *str3)
{
	char *cat_str;

	/* size of memory = str1 + str2 + str3 + \0 */
	cat_str = malloc(_strlen(str1) + _strlen(str2) + _strlen(str3) + 1);
	if (cat_str == NULL)
		return (NULL);
	_strcpy(cat_str, str1);
	_strcat(cat_str, str2);
	_strcat(cat_str, str3);
	return (cat_str);
}

/**
 * _puts_n - prints a string
 * @str: a string
 *
 * Return: void
 */
void _puts_n(char *str)
{
	int i;

	for (i = 0; *(str + i) != '\0'; i++)
		_putchar(*(str + i));
}
