#include "main.h"

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

/**
 * _which - a function that finds a file
 * @file_name: name of the file
 * @env_var: environment variable to search file in
 *
 * Return: absolute path of the file if found, or
 *		NULL if it is not found or if an error occurred
 */
char *_which(char *file_name, char *env_var)
{
	char **path_arr, *test_path, *path;
	int i, result = -1;
	struct stat file_status;

	if (file_name == NULL)
		return (NULL);
	path = _getenv_value(env_var);
	path_arr = get_tokens(path, ":"); /* FREE this */
	for (i = 0; path_arr[i] != NULL; i++)
	{
		if (file_name[0] == '/')
			test_path = _strdup(file_name);
		else
			test_path = concat_strings(path_arr[i], "/", file_name);
		if (test_path == NULL)
		{
			perror("Memory allocation failed ");
			break;
		}
		result = stat(test_path, &file_status);
		if (result == 0)
			break;
		free(test_path);
		test_path = NULL;
	}
	for (i = 0; path_arr[i] != NULL; i++)
		free(path_arr[i]);
	free(path_arr);
	return (test_path);
}

/**
 * _setenv - a function that adds or changes an environment variable
 * @name: name of the variable
 * @value: value of the variable
 *
 * Return: 0 on success, or -1 on failure
 */
int _setenv(const char *name, const char *value)
{
	int i, env_size = 0, var_exists;
	char **cur_env = environ, **new_env, *old_var, *new_var;

	if (name == NULL || *name == '\0' || (_strchr(name, '=') != NULL))
		return (-1);
	old_var = _getenv_var(name);
	var_exists = old_var != NULL;
	/* prepare new variable */
	new_var = concat_strings(name, "=", value);
	if (new_var == NULL)
		return (-1);
	/* copy environ */
	env_size = 0;
	while (cur_env[env_size] != NULL)
		env_size++;
	if (!var_exists)
		env_size++;
	new_env = malloc(sizeof(char *) * (env_size + 1));
	if (new_env == NULL)
		return (-1);
	for (i = 0; i < env_size; i++)
	{
		/* happens only if var exists */
		if (old_var == cur_env[i])
		{
			free(cur_env[i]);
			new_env[i] = new_var;
		}
		else
			new_env[i] = cur_env[i];
	}
	if (!var_exists)
		new_env[env_size - 1] = new_var;
	new_env[env_size] = NULL;
	environ = new_env;
	free(cur_env);
	return (0);
}

/**
 * _unsetenv - a function that adds or changes an environment variable
 * @name: name of the variable
 *
 * Return: 0 on success, or -1 on failure
 */
int _unsetenv(const char *name)
{
	int i, j, env_size = 0, var_exists;
	char **cur_env = environ, **new_env, *old_var;

	if (name == NULL || *name == '\0' || (_strchr(name, '=') != NULL))
		return (-1);
	old_var = _getenv_var(name);
	var_exists = old_var != NULL;
	if (!var_exists)
		return (0);
	/* copy environ */
	env_size = 0;
	while (cur_env[env_size] != NULL)
		env_size++;
	if (var_exists)
		env_size--;
	new_env = malloc(sizeof(char *) * (env_size + 1));
	if (new_env == NULL)
		return (-1);
	for (i = 0, j = 0; i <= env_size; i++, j++)
	{
		/* happens only if var exists */
		if (old_var == cur_env[j])
		{
			free(cur_env[j]);
			i--;
		}
		else
			new_env[i] = cur_env[j];
	}
	new_env[env_size] = NULL;
	environ = new_env;
	free(cur_env);
	return (0);
}
