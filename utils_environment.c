#include "main.h"

/**
 * _which - a function that finds a file
 * @file: name of the file
 *
 * Return: absolute path of the file if found, or
 *		NULL if it is not found or if an error occurred
 */
char *_which(char *file)
{
	char *path = NULL, **path_arr = NULL, *full_path = NULL;
	int i, success = 0;
	struct stat file_status;

	if (file == NULL)
		return (NULL);
	if (*file == '/' || *file == '.')
	{
		success = stat(file, &file_status) == 0;
		if (success)
			return (_strdup(file));
		return (NULL);
	}
	path = _getenv_value("PATH");
	path_arr = get_tokens(path, ":"); /* FREE this */
	for (i = 0; path_arr && path_arr[i] != NULL; i++)
	{
		if (chdir(path_arr[i]) == -1)
			return (NULL);
		success = stat(file, &file_status) == 0;
		if (success)
		{
			full_path = concat_strings(path_arr[i], "/", file);
			chdir(_getenv_value("PWD"));
			break;
		}
	}
	free_string_array(path_arr);
	return (full_path);
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

/**
 * _getenv_var - gets the address of the variable in the environ
 * @name: name of the variable
 *
 * Return: value of the variable, or NULL if there are errors
 *			or if the variable doesn't exist
 */
char *_getenv_var(const char *name)
{
	char *var_cpy, *variable, *save_ptr = NULL, *var_ptr = NULL;
	int i, is_variable = 0;

	if (name == NULL || environ == NULL || (_strchr(name, '=') != NULL))
		return (NULL);
	for (i = 0; environ[i] != NULL; i++, save_ptr = NULL)
	{
		var_cpy = _strdup(environ[i]);
		variable = _strtok_r(var_cpy, "=", &save_ptr);
		is_variable = _strcmp(variable, name) == 0;
		free(var_cpy);
		if (is_variable)
			break;
	}
	if (is_variable)
		var_ptr = environ[i];
	return (var_ptr);
}

/**
 * _getenv_value - gets the address of the value of a variable in the environ
 * @name: name of the variable
 *
 * Return: value of the variable, or NULL if there are errors
 *			or if the variable doesn't exist
 */
char *_getenv_value(const char *name)
{
	char *var_cpy, *variable, *save_ptr = NULL, *value_ptr = NULL;
	int i, is_variable = 0;

	if (name == NULL || environ == NULL || (_strchr(name, '=') != NULL))
		return (NULL);
	for (i = 0; environ[i] != NULL; i++, save_ptr = NULL)
	{
		var_cpy = _strdup(environ[i]);
		variable = _strtok_r(var_cpy, "=", &save_ptr);
		is_variable = _strcmp(variable, name) == 0;
		free(var_cpy);
		if (is_variable)
			break;
	}
	if (is_variable)
	{
		value_ptr = _strchr(environ[i], '=');
		value_ptr++;
	}
	return (value_ptr);
}
