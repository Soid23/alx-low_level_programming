#include "lists.h"

/**
 * list_len - returns the number of elements in a linked list_t list.
 * @h: pointer`
 * Return: number of elements
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		a++;
		h = h->next;
	}
	return (a);
}

