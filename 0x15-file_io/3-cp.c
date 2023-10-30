#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *creat_buff(char *filename);
void close_file(int pfile);

/**
 * creat_buff - Allocates 1024 bytes for a buffer.
 * @filename: pointer to file buffer to store chars
 * Return: pointer to new buffer
 */

char *creat_buff(char *filename)
{
	char *buff;

	buff = malloc(sizeof(char) * 1024);
	if (buff == NULL)
	{
		dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", filename);
		exit(99);
	}
	return (buff);
}

/**
 * close_file - closes file descripts
 * @pfile: file to be closed
 */

void close_file(int pfile)
{
	int x;

	x = close(pfile);
	if (x == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", pfile);
		exit(100);
	}
}

/**
 * main - copies the contents of a file to another file
 * @argc: agruments number
 * @argv: pointer to arguments
 * Return: 0 success always
 */

int main(int argc, char *argv[])
{
	int from, to, r, w;
	char *buffer;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	buffer = creat_buff(argv[2]);
	from = open(argv[1], O_RDONLY);
	r = read(from, buffer, 1024);
	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	do {
		if (from == -1 || r == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't read from file %s\n", argv[1]);
			free(buffer);
			exit(98);
		}

		w = write(to, buffer, r);
		if (to == -1 || w == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", argv[2]);
			free(buffer);
			exit(99);
		}

		r = read(from, buffer, 1024);
		to = open(argv[2], O_WRONLY | O_APPEND);

	} while (r > 0);

	free(buffer);
	close_file(from);
	close_file(to);

	return (0);
}
