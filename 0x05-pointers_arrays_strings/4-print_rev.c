#include "main.h"

/**
 * print_rev -  prints a string, in reverse followed by a new line.
 *
 * @s : string to print
 */
void print_rev(char *s)
{
	int i, k, len;

	i = 0;

	while (s[i] != '\0')
	{
		i++;
	}

	len = i;

	for (k = len - 1; k >= 0; k--)
	{
		putchar(s[k]);
	}

	 putchar('\n');
}

