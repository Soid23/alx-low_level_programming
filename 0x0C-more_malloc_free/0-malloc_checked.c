#include "main.h"

/**
 * *malloc_checked - allocates memory using malloc.
 * @b : bytes to be allocated.
 * Return : to the pointer.
 */

void *malloc_checked(unsigned int b)
{
	void *f;

	f = (malloc)b;
	if (f == NULL)
		exit(98);
	return (f);
}
