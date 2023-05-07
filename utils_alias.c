#include "main.h"

/**
 * print_alias_list - prints all the elements of the alias list
 * @h: pointer to the head of the alias list
 *
 * Return: void
 */
void print_alias_list(const alias_t *h)
{
	while (h != NULL)
	{
		_puts_n(h->alias_name);
		_puts_n("=\'");
		_puts_n(h->real_name);
		_puts_n("\'\n");
		h = h->next;
	}
}

/**
 * print_alias_node - finds and prints a node with a given alias name
 * @h: pointer to the head of the alias list
 * @given_name: given alias name
 *
 * Return: 0 on success, or 1 on error
 */
int print_alias_node(const alias_t *h, char *given_name)
{
	alias_t *node = NULL;

	node = search_alias_list(h, given_name);
	if (node != NULL)
	{
		_puts_n(node->alias_name);
		_puts_n("=\'");
		_puts_n(node->real_name);
		_puts_n("\'\n");
		return (CMD_EXIT_SUCCESS);
	}
	return (CMD_ALIAS_FAILURE);
}

/**
 * add_alias_node - a function that adds a new node at
 *					the beginning of the alias list.
 * @head: a double pointer to the head of the alias list
 * @arg: the alias argument to be the new node in the list
 *
 * Return: 0 on success, or 1 on error
 */
int add_alias_node(alias_t **head, char *arg)
{
	alias_t *new_alias, *prev, *current;
	char *alias_name = NULL, *real_name = NULL, *save_ptr = NULL;

	if (head == NULL || arg == NULL)
		return (CMD_ALIAS_FAILURE);
	alias_name = _strtok_r(arg, "=", &save_ptr);
	real_name = _strtok_r(NULL, "=", &save_ptr);
	new_alias = search_alias_list(*head, alias_name);
	if (new_alias != NULL)
	{
		free(new_alias->real_name);
		new_alias->real_name = _strdup(real_name);
		if (new_alias->real_name == NULL)
			return (CMD_ALIAS_FAILURE);
		return (CMD_EXIT_SUCCESS);
	}
	new_alias = malloc(sizeof(alias_t));
	if (new_alias == NULL)
		return (CMD_ALIAS_FAILURE);
	new_alias->alias_name = _strdup(alias_name);
	new_alias->real_name = _strdup(real_name);
	new_alias->next = NULL;
	current = *head;
	while (current != NULL)
	{
		prev = current;
		current = current->next;
	}
	if (*head == NULL)
		*head = new_alias;
	else
		prev->next = new_alias;
	return (CMD_EXIT_SUCCESS);
}

/**
 * search_alias_list - searches for a node with the given
 *					alias name in the alias list
 * @head: head of the alias list
 * @given_name: given alias name to search for
 *
 * Return: pointer to the node if found, NULL otherwise
 */
alias_t *search_alias_list(const alias_t *head, char *given_name)
{
	while (head != NULL)
	{
		if (_strcmp(head->alias_name, given_name) == 0)
			return ((alias_t *)head);
		head = head->next;
	}
	return (NULL);
}

/**
 * substitute_alias - substitutes a command, if it is an alias
 *					with the real command
 * @head: head of the alias list
 * @cmd: command
 *
 * Return: pointer to the substituted command, if it is an alias
 */
char *substitute_alias(alias_t *head, char *cmd)
{
	alias_t *cmd_alias = NULL;
	char *cmd_0 = NULL, *cmd_args = NULL, *cmd_cpy;

	cmd_cpy = _strdup(cmd);
	if (cmd_cpy == NULL)
		return (cmd);
	cmd_0 = _strtok_r(cmd, " \t", &cmd_args);
	cmd_alias = search_alias_list(head, cmd_0);
	while (cmd_alias != NULL)
	{
		free(cmd_cpy);
		cmd_cpy = concat_strings(cmd_alias->real_name, " ", cmd_args);
		cmd_alias = search_alias_list(head, cmd_alias->real_name);
	}
	return (cmd_cpy);
}
