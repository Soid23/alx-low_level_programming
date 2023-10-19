#include "lists.h"

/**
 * free_list - frees a list_t list.
 * @head: to be freed.
 */
void free_list(list_t *head)
{
	list_t *heap_node;

	while ((heap_node = head) != NULL)
	{
		head = head->next;
		free(heap_node->str);
		free(heap_node);
	}
}
