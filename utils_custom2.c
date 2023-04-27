#include "main.h"

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

	if (str1 == NULL || str2 == NULL || str3 == NULL)
		return (NULL);
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
