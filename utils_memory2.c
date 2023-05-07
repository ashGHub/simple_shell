#include "main.h"

/**
 * free_alias_list - a function that frees a list_t list
 * @head: head of the linked list
 *
 * Return: void
 */
void free_alias_list(alias_t *head)
{
	alias_t *prev;

	while (head != NULL)
	{
		prev = head;
		head = head->next;
		free(prev->alias_name);
		free(prev->real_name);
		free(prev);
	}
}
