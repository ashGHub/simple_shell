#include "main.h"

/**
 * free_line - frees memory held by shell data
 * @shell: shell data
 *
 * Return: void
 */
void free_line(shell_t *shell)
{
	free(shell->line_buf);
	shell->line_buf = NULL;
	shell->line_size = 0;
	free_string_array(shell->line_arr);
}

/**
 * free_string_array - frees a dynamically allocated array strings
 *					that is NULL terminated
 * @str_arr: an array of strings
 *
 * Return: void
 */
void free_string_array(char **str_arr)
{
	int i;

	for (i = 0; str_arr && str_arr[i]; i++)
		free(str_arr[i]);
	free(str_arr);
	str_arr = NULL;
}

/**
 * free_environ - frees new allocated memory in the environ
 * @shell: shell data
 *
 * Return: void
 */
void free_environ(shell_t *shell)
{
	int i;
	char **cur_env = environ;

	environ = shell->envp;
	for (i = 0; cur_env[i] != NULL; i++)
		free(cur_env[i]);
	free(cur_env);
	cur_env = NULL;
}

/**
 * free_shell - frees memory held by shell data
 * @shell: shell data
 *
 * Return: void
 */
void free_shell(shell_t *shell)
{
	free_line(shell);
	free_string_array(shell->cmd_argv);
	free_environ(shell);
	free_alias_list(shell->alias_head);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer to the memory block to be reallocated
 * @old_size: old size of the old memory block
 * @new_size: new size of the reallocated memory block
 *
 * Return: pointer to the reallocated memory,
 * or if new size == 0 and ptr is not NULL, it will free(ptr) and return NULL
 * or if new_size == old_size, it will return ptr
 * or if ptr == NULL, it is equivalent to malloc(new_size)
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i, copy_size;
	void *mem;

	/* If new_size = 0 and ptr is not NULL */
	/* realloc is equivalent to -> free(ptr) */
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	/* If new_size = old_size, no new memory allocation is required */
	if (new_size == old_size)
		return (ptr);

	mem = malloc(new_size);
	if (mem == NULL)
		return (NULL);
	mem = _memset(mem, '\0', new_size); /* initialize heap allocation */
	/* If ptr = NULL, it is equivalent to -> malloc(new_size) */
	if (ptr == NULL)
		return (mem);

	copy_size = new_size < old_size ? new_size : old_size;
	for (i = 0; i < copy_size; i++)
		*((char *) mem + i) = *((char *) ptr + i);
	free(ptr);

	return (mem);
}
